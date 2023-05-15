/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:41:31 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/13 17:17:34 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_lone_builtin(t_cmd **lst, char ***ep, pid_t *pids);
static void	handle_exit_codes(pid_t	*pids);

void	executor(t_cmd **lst, char ***ep)
{
	int		i;
	int		next;
	int		fd_read_prev;
	pid_t	*pids;

	pids = dmy_malloc(sizeof(pid_t) * (get_nb_cmd(lst) + 1));
	if (pids == NULL || lst == NULL || *lst == NULL)
		return ;
	if (lst[1] == NULL && lst[0]->builtin != NULL)
		handle_lone_builtin(lst, ep, pids);
	if (lst[1] == NULL && lst[0]->builtin != NULL)
		return ;
	fd_read_prev = -1;
	i = -1;
	while (lst[++i])
	{
		next = TRUE;
		if (lst[i + 1] == NULL)
			next = FALSE;
		process_redirections(lst[i]);
		pids[i] = prepare_and_exec(lst[i], *ep, next, &fd_read_prev);
	}
	pids[i] = 0;
	handle_exit_codes(pids);
	dmy_free(pids);
}

static void	handle_lone_builtin(t_cmd **lst, char ***ep, pid_t *pids)
{
	g_exit_code = lst[0]->builtin(lst[0]->args, ep);
	dmy_free(pids);
}

/*
void	executor(t_cmd **lst, char ***ep)
{
	int		i;
	int		next;
	int		fd_read_prev;
	pid_t	*pids;

	pids = dmy_malloc(sizeof(pid_t) * (get_nb_cmd(lst) + 1));
	if (pids == NULL || lst == NULL || *lst == NULL)
		return ;
	i = 0;
	if (lst[1] == NULL && lst[0]->builtin != NULL)
		g_exit_code = lst[0]->builtin(lst[0]->args, ep);
	else
		i = -1;
	fd_read_prev = -1;
	while (lst[++i])
	{
		next = TRUE;
		if (lst[i + 1] == FALSE)
			next = FALSE;
		process_redirections(lst[i]);
		pids[i] = prepare_and_exec(lst[i], *ep, next, &fd_read_prev);
	}
	pids[i] = 0;	
	handle_exit_codes(pids);
	dmy_free(pids);
}*/

static void	handle_exit_codes(pid_t	*pids)
{
	int	i;

	i = 0;
	while (pids[i])
	{
		waitpid(pids[i], &g_exit_code, 0);
		i++;
	}
	if (g_exit_code >= 255)
		g_exit_code %= 255;
}
