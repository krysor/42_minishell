/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:41:31 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/20 17:36:18 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_nb_cmd(t_cmd **lst);
static int	builtin_is_alone_and_modifies_current_process(t_cmd **lst);
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
	if (builtin_is_alone_and_modifies_current_process(lst))
	{
		g_exit_code = lst[0]->builtin(lst[0]->args, ep);
		dmy_free(pids);
		return ;
	}
	fd_read_prev = -1;
	i = -1;
	while (lst[++i])
	{
		next = TRUE;
		if (lst[i + 1] == NULL)
			next = FALSE;
		pids[i] = prepare_and_exec(lst[i], *ep, next, &fd_read_prev);
	}
	pids[i] = 0;
	handle_exit_codes(pids);
}

static int	get_nb_cmd(t_cmd **lst)
{	
	int	nb_cmd;

	if (lst == NULL || *lst == NULL)
		return (0);
	nb_cmd = 0;
	while (lst[nb_cmd] != NULL)
		nb_cmd++;
	return (nb_cmd);
}

static int	builtin_is_alone_and_modifies_current_process(t_cmd **lst)
{
	if (lst[1] == NULL && lst[0]->builtin != NULL
		&& (lst[0]->builtin == &ft_cd
			|| lst[0]->builtin == &ft_export
			|| lst[0]->builtin == &ft_unset
			|| lst[0]->builtin == &ft_exit))
		return (TRUE);
	return (FALSE);
}

static void	handle_exit_codes(pid_t	*pids)
{
	int	i;

	i = 0;
	while (pids[i])
	{
		waitpid(pids[i], &g_exit_code, 0);
		i++;
	}
	if (WIFEXITED(g_exit_code) == TRUE)
		g_exit_code = WEXITSTATUS(g_exit_code);
	else if (WIFSIGNALED(g_exit_code) == TRUE)
	{
		if (WTERMSIG(g_exit_code) == SIGINT
			|| WTERMSIG(g_exit_code) == SIGQUIT)
			g_exit_code += 128;
	}
	dmy_free(pids);
}

void	close_open_fds(t_cmd **lst)
{
	int	i;

	if (lst == NULL)
		return ;
	i = 0;
	while (lst[i])
	{
		if (lst[i]->fd_in >= 0)
			close(lst[i]->fd_in);
		if (lst[i]->fd_out >= 0)
			close(lst[i]->fd_out);
		i++;
	}
}
