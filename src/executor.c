/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:41:31 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/17 17:04:28 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		process_redirections(void)
{
	return (0);
}

int		get_oflag(char *type)
{
	int	oflag;

	oflag = 0;
	if (ft_strncmp(type, "<", 2))
		oflag |= O_RDONLY;
	else if (ft_strncmp(type, ">", 2) == 0)
	{
		oflag |= O_WRONLY;
		if (ft_strncmp(type, ">>", 3) == 0)
			oflag|= O_APPEND;
	}
	else
		yikes("wrong input for get_oflag\n", 0);
	return (oflag);
}

int		get_rdr_fd(char *type)
{
	if (ft_strncmp(type, "<", 2))
		return (STDIN_FILENO);
	else if (ft_strncmp(type, ">", 2) || ft_strncmp(type, ">>", 3) == 0)
		return (STDOUT_FILENO);
	else
		yikes("wrong input for get_oflag\n", 0);
	return (-1);
}

// opens the file with the right flags and redirects the stdin/stdout accordingly
int		handle_rdr(char *type, char *arg)
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

// question: how to dup2() back the default standard output / input
void	prepare_and_exec(t_cmd *cmd, char *ep[])
{
	t_rdr	*current;
	int		pipefd[2];
	pid_t	pid;
	
	(void)cmd;
	(void)ep;

	(void)current;
	if (pipe(pipefd) == -1)
		yikes("pipe failed", 0);
	pid = fork();
	if (pid == -1)
		yikes("fork() failed", 0);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(STDOUT_FILENO, pipefd[1]) == -1)
			yikes("dup2() failed", 0);
		close(pipefd[1]);
		if (process_redirections() == -1)
			yikes("processing of redirections failed\n", 0);

		if (cmd->builtin) 
			exit(cmd->builtin(cmd->args, &ep));
		if (execve(cmd->file, cmd->args, ep) == -1)
			exit(-1);//gotta exit in case of a wrong cmd <ultra fast parrot>
	}
	else
	{
		close(pipefd[1]);
		if (dup2(STDIN_FILENO, pipefd[0]) == -1)
			yikes("dup2() failed", 0);
		close(pipefd[0]);
		if (waitpid(pid, NULL, 0) == -1)
			yikes("waitpid() failed", 0);
	}
}

void	executor(t_cmd **lst, char ***ep)
{
	int	i;
	
	if (!lst || !*lst)
	 	return ;
	i = 1;
	if (lst[1] == NULL && lst[0]->builtin)
		lst[0]->builtin(lst[0]->args, ep);
	else
		i = 0;
	while (lst[i])
		prepare_and_exec(lst[i++], *ep);
}
