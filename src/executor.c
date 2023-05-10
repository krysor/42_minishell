/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:41:31 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/09 17:36:47 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_redirections(void)
{
	return (0);
}

int	get_oflag(char *type)
{
	int	oflag;

	oflag = 0;
	if (ft_strncmp(type, "<", 2))
		oflag |= O_RDONLY;
	else if (ft_strncmp(type, ">", 2) == 0)
	{
		oflag |= O_WRONLY;
		if (ft_strncmp(type, ">>", 3) == 0)
			oflag |= O_APPEND;
	}
	else
		yikes("wrong input for get_oflag\n", 0);
	return (oflag);
}

int	get_rdr_fd(char *type)
{
	if (ft_strncmp(type, "<", 2))
		return (STDIN_FILENO);
	else if (ft_strncmp(type, ">", 2) || ft_strncmp(type, ">>", 3) == 0)
		return (STDOUT_FILENO);
	else
		yikes("wrong input for get_oflag\n", 0);
	return (-1);
}

// opens the file with the right flags
//		and redirects the stdin/stdout accordingly
int	handle_rdr(char *type, char *arg)
{
	int	fd;

	fd = open(arg, get_oflag(type));
	if (fd == -1)
		return (1);
	if (dup2(fd, get_rdr_fd(type)) == -1)
		return (1);
	close(fd);
	return (0);
}

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
