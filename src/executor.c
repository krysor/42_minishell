/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:41:31 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/11 10:08:48 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executor(t_cmd **lst, char ***ep)
{
	int	i;
	int	next;
	int	fd_read_prev;

	pid_t	*pids;
	pids = dmy_malloc(sizeof(pid_t) * (get_nb_cmd(lst) + 1));

	if (!lst || !*lst)
		return ;
	i = 1;
	if (lst[1] == NULL && lst[0]->builtin)
		g_exit_code = lst[0]->builtin(lst[0]->args, ep);
	else
		i = 0;
	fd_read_prev = -1;
	while (lst[i])
	{
		next = TRUE;
		if (!lst[i + 1])
			next = FALSE;
		process_redirections(lst[i]);
		pids[i] = prepare_and_exec(lst[i], *ep, next, &fd_read_prev);
		i++;
	}
	pids[i] = 0;
	i = -1;
	while (pids[++i])
		waitpid(pids[i], &g_exit_code, 0);
	if (g_exit_code >= 255)
		g_exit_code %= 255;
	dmy_free(pids);
}
