/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:41:31 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/15 16:14:12 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	builtin_is_alone_and_non_rdr(t_cmd **lst);
static void	handle_alone_builtin(t_cmd **lst, char ***ep, pid_t *pids);
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
	if (builtin_is_alone_and_non_rdr(lst))
	{
		handle_alone_builtin(lst, ep, pids);
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

static int	builtin_is_alone_and_non_rdr(t_cmd **lst)
{
	if (lst[1] == NULL && lst[0]->builtin != NULL
		&& (lst[0]->builtin == &ft_cd
			|| lst[0]->builtin == &ft_export
			|| lst[0]->builtin == &ft_unset
			|| lst[0]->builtin == &ft_exit))
		return (TRUE);
	return (FALSE);
}

static void	handle_alone_builtin(t_cmd **lst, char ***ep, pid_t *pids)
{
	process_redirections(lst[0]);
	if (lst[0]->fd_in >= 0)
		close(lst[0]->fd_in);
	if (lst[0]->fd_out >= 0)
		close(lst[0]->fd_out);
	g_exit_code = lst[0]->builtin(lst[0]->args, ep);
	dmy_free(pids);
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

/*
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

	// if (WIFSIGNALED(g_exit_code) == TRUE
	// 	&& (g_exit_code == 2 || g_exit_code == 3))
	// 	g_exit_code += 128;
	dmy_free(pids);
}*/
