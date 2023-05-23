/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:04:06 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/23 12:14:20 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child(int *fd_read_prev, int *pipefd, int next, t_cmd *cmd);
static void	print_error_message_and_set_exit_code(char *pathname);
static void	parent(int next, int *pipefd, int *fd_read_prev);

/*
pid_t	prepare_and_exec(t_cmd *cmd, char *ep[], int next, int *fd_read_prev)
{
	int		pipefd[2];
	pid_t	pid;

	if (next && (pipe(pipefd)))
		yikes("pipe failed", 0);
	pid = fork();
	if (pid == -1)
		yikes("fork() failed", 0);
	if (pid == 0)
	{
		child(fd_read_prev, pipefd, next, cmd);
		if (cmd->builtin)
			g_exit_code = cmd->builtin(cmd->args, &ep);
		else if (cmd->file != NULL && execve(cmd->file, cmd->args, ep) == -1)
		{
			if (cmd->file != NULL && access(cmd->file, F_OK)
				&& ft_memchr(cmd->file, '/', ft_strlen(cmd->file)) == NULL)
			{
				ft_putstr_fd(cmd->file, STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
			}
			else
				perror(cmd->file);
			if (errno == EACCES || errno == ENOTDIR)
				g_exit_code = 126;
			else if (errno == ENOENT || errno != 0)
				g_exit_code = 127;
		}
		exit(g_exit_code);
	}
	else
		parent(next, pipefd, fd_read_prev);
	return (pid);
}*/

pid_t	prepare_and_exec(t_cmd *cmd, char *ep[], int next, int *fd_read_prev)
{
	int		pipefd[2];
	pid_t	pid;

	if (next && (pipe(pipefd)))
		yikes("pipe failed", 0);
	pid = fork();
	if (pid == -1)
		yikes("fork() failed", 0);
	if (pid == 0)
	{
		child(fd_read_prev, pipefd, next, cmd);
		if (g_exit_code == INT_MIN)
			;
		else if (cmd->builtin)
			g_exit_code = cmd->builtin(cmd->args, &ep);
		else if (cmd->file != NULL && execve(cmd->file, cmd->args, ep) == -1)
			print_error_message_and_set_exit_code(cmd->file);
		exit(g_exit_code);
	}
	else
		parent(next, pipefd, fd_read_prev);
	return (pid);
}

static void	child(int *fd_read_prev, int *pipefd, int next, t_cmd *cmd)
{
	if (cmd->fd_in >= 0 && dup2(cmd->fd_in, STDIN_FILENO) == -1)
		yikes("dup2() failed", 0);
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (*fd_read_prev != -1)
	{
		if (cmd->fd_in < 0 && dup2(*fd_read_prev, STDIN_FILENO) == -1)
			yikes("dup2() failed", 0);
		if (close(*fd_read_prev))
			yikes("close fd_read_prev child failed", 0);
	}
	if (cmd->fd_out >= 0 && dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		yikes("dup2() failed", 0);
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
	if (next)
	{
		if (close(pipefd[READ]))
			yikes("close(pipefd[0]) child failed", 0);
		if (cmd->fd_out < 0 && dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
			yikes("dup2() failed", 0);
		if (close(pipefd[WRITE]))
			yikes("close(pipefd[1]) child failed", 0);
	}
}

static void	print_error_message_and_set_exit_code(char *pathname)
{
	if (pathname != NULL && access(pathname, F_OK)
		&& ft_memchr(pathname, '/', ft_strlen(pathname)) == NULL)
	{
		ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	else
		perror(pathname);
	if (errno == EACCES || errno == ENOTDIR)
		g_exit_code = 126;
	else if (errno == ENOENT || errno != 0)
		g_exit_code = 127;
}

static void	parent(int next, int *pipefd, int *fd_read_prev)
{
	if (next && close(pipefd[WRITE]))
		yikes("close(pipefd[1]) parent failed", 0);
	if (*fd_read_prev != -1 && close(*fd_read_prev))
		yikes("close(fd_read_prev) parent failed", 0);
	*fd_read_prev = pipefd[READ];
}
