/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:04:06 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/08 09:51:04 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child(int *fd_read_prev, int *pipefd, int next);
static void	parent(pid_t pid, int next, int *pipefd, int *fd_read_prev);

void	prepare_and_exec(t_cmd *cmd, char *ep[], int next, int *fd_read_prev)
{
	int		pipefd[2];
	pid_t	pid;
	int		exit_code;

	if (next && (pipe(pipefd)))
		yikes("pipe failed", 0);
	pid = fork();
	if (pid == -1)
		yikes("fork() failed", 0);
	if (pid == 0)
	{
		child(fd_read_prev, pipefd, next);
		if (cmd->builtin)
		{
			exit_code = cmd->builtin(cmd->args, &ep);
			dmy_freeall();
			exit(exit_code);
		}
		if (execve(cmd->file, cmd->args, ep) == -1)
		{
			dmy_freeall();
			exit(-1);
		}
	}
	else
		parent(pid, next, pipefd, fd_read_prev);
}

static void	child(int *fd_read_prev, int *pipefd, int next)
{
	if (*fd_read_prev != -1)
	{
		if (dup2(*fd_read_prev, STDIN_FILENO) == -1)
			yikes("dup2() failed", 0);
		if (close(*fd_read_prev))
			yikes("close fd_read_prev child failed", 0);
	}
	if (next)
	{
		if (close(pipefd[0]))
			yikes("close(pipefd[0]) child failed", 0);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			yikes("dup2() failed", 0);
		if (close(pipefd[1]))
			yikes("close(pipefd[1]) child failed", 0);
	}
}

static void	parent(pid_t pid, int next, int *pipefd, int *fd_read_prev)
{
	if (next && close(pipefd[1]))
		yikes("close(pipefd[1]) parent failed", 0);
	if (*fd_read_prev != -1 && close(*fd_read_prev))
		yikes("close(fd_read_prev) parent failed", 0);
	*fd_read_prev = pipefd[0];
	if (!next && waitpid(pid, NULL, 0) == -1)
		yikes("waitpid failed", 0);
}

/*
void	prepare_and_exec(t_cmd *cmd, char *ep[], int next, int *fd_read_prev)
{
	int		pipefd[2];
	pid_t	pid;

	(void)cmd;
	(void)ep;
	if (next && (pipe(pipefd)))
		yikes("pipe failed", 0);
	pid = fork();
	if (pid == -1)
		yikes("fork() failed", 0);
	if (pid == 0)
	{
		if (*fd_read_prev != -1)
		{
			if (dup2(*fd_read_prev, STDIN_FILENO) == -1)
				yikes("dup2() failed", 0);
			if (close(*fd_read_prev))
				yikes("close fd_read_prev child failed", 0);
		}
		if (next)
		{
			if (close(pipefd[0]))
				yikes("close(pipefd[0]) child failed", 0);
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				yikes("dup2() failed", 0);
			if (close(pipefd[1]))
				yikes("close(pipefd[1]) child failed", 0);
		}
		if (cmd->builtin)
			exit(cmd->builtin(cmd->args, &ep));
		if (execve(cmd->file, cmd->args, ep) == -1)
			exit(-1);
	}
	else
	{	
		if (next && close(pipefd[1]))
			yikes("close(pipefd[1]) parent failed", 0);
		if (*fd_read_prev != -1 && close(*fd_read_prev))
			yikes("close(fd_read_prev) parent failed", 0);
		*fd_read_prev = pipefd[0];
		if (!next && waitpid(pid, NULL, 0) == -1)
			yikes("waitpid failed", 0);
	}
}*/
