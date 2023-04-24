/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:41:31 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/24 17:23:43 by kkaczoro         ###   ########.fr       */
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

void	prepare_and_exec(t_cmd *cmd, char *ep[], int next, int i)
{
	int		pipefd[2];
	int		pipefd_uneven[2];
	int		*pipep;
	pid_t	pid;
	
	(void)cmd;
	(void)ep;

	if (next && ((i % 2 && pipe(pipefd_uneven)) || pipe(pipefd)))
		yikes("pipe failed", 0);
	pid = fork();
	if (pid == -1)
		yikes("fork() failed", 0);
	if (pid == 0)
	{
		if (i > 0)
		{
			pipep = pipefd_uneven;
			if (i % 2)
				pipep = pipefd;
			if (close(pipep[1]))
				yikes("close(pipefd[0]) child failed", 0);
			if (dup2(pipep[0], STDIN_FILENO) == -1)
				yikes("dup2() failed", 0);
			if (close(pipep[0]))
				yikes("close(pipefd[1]) child failed", 0);
		}
		if (next)
		{
			pipep = pipefd;
			if (i % 2)
				pipep = pipefd_uneven;
			if (close(pipep[0]))
				yikes("close(pipefd[0]) child failed", 0);
			if (dup2(pipep[1], STDOUT_FILENO) == -1)
				yikes("dup2() failed", 0);
			if (close(pipep[1]))
				yikes("close(pipefd[1]) child failed", 0);
		}
		if (cmd->builtin)
			exit(cmd->builtin(cmd->args, &ep));
		if (execve(cmd->file, cmd->args, ep) == -1)
			exit(-1);//gotta exit in case of a wrong cmd <ultra fast parrot>
	}
	else
	{	
		if (i > 0 && i % 2)
		{
			close(pipefd[1]);
			close(pipefd[0]);
		}
		else if (i > 0)
		{
			close(pipefd_uneven[1]);
			close(pipefd_uneven[0]);
		}
		// if (!next)
		// 	system("lsof -c minishell");
		if (!next && waitpid(pid, NULL, 0) == -1)
			yikes("waitpid failed", 0);
	}
}


// void	prepare_and_exec(t_cmd *cmd, char *ep[], int next, int i)
// {
// 	int		pipefd[2];
// 	// int		pipefd_uneven[2];
// 	pid_t	pid;
// 	//int		fd_last;
	
// 	(void)i;
// 	(void)cmd;
// 	(void)ep;

// 	if (next && pipe(pipefd) == -1)
// 		yikes("pipe failed", 0);
// 	pid = fork();
// 	//fd_last = STDIN_FILENO;
// 	if (pid == -1)
// 		yikes("fork() failed", 0);
// 	if (pid == 0)
// 	{
// 		if (next)
// 		{
// 			if (close(pipefd[0]))
// 				yikes("close(pipefd[0]) child failed", 0);
// 			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
// 				yikes("dup2() failed", 0);
// 			if (close(pipefd[1]))
// 				yikes("close(pipefd[1]) child failed", 0);
// 		}
// 		else
// 		{
// 			if (close(pipefd[1]))
// 				yikes("close(pipefd[0]) child failed", 0);
// 			if (dup2(pipefd[0], STDIN_FILENO) == -1)
// 				yikes("dup2() failed", 0);
// 			if (close(pipefd[0]))
// 				yikes("close(pipefd[1]) child failed", 0);
// 		}
// 		printf("right before exec\n");
// 		if (cmd->builtin)
// 			exit(cmd->builtin(cmd->args, &ep));
// 		if (execve(cmd->file, cmd->args, ep) == -1)
// 			exit(-1);//gotta exit in case of a wrong cmd <ultra fast parrot>
// 	}
// 	else if (next)
// 	{
// 		// if (close(pipefd[1]))
// 		// 	yikes("close(pipefd[1]) parent failed", 0);

// 		// fd_last = dup2(pipefd[0], STDIN_FILENO);
// 		// if (fd_last == -1)
// 		// 		yikes("dup2() failed", 0);

// 		// if (close(pipefd[0]))
// 		// 	yikes("close(pipefd[0]) parent failed", 0);
// 	}
// 	else
// 	{
// 		//dup2(fd_last, STDIN_FILENO);
// 		close(pipefd[1]);
// 		// close(pipefd[0]);
		
// 		if (waitpid(pid, NULL, 0) == -1)
// 			yikes("waitpid failed", 0);
// 	}
// }

/*
// question: how to dup2() back the default standard output / input
void	prepare_and_exec(t_cmd *cmd, char *ep[], int next)
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
		// if (dup2(STDOUT_FILENO, pipefd[1]) == -1)

		if (next && dup2(pipefd[1], STDOUT_FILENO) == -1)
			yikes("dup2() failed", 0);
			
		close(pipefd[1]);
		
		// if (process_redirections() == -1)
		// 	yikes("processing of redirections failed\n", 0);

		if (cmd->builtin) 
			exit(cmd->builtin(cmd->args, &ep));
		//printf("before execve\n");
		if (execve(cmd->file, cmd->args, ep) == -1)
			exit(-1);//gotta exit in case of a wrong cmd <ultra fast parrot>
		//printf("after execve\n");
	}
	else
	{
		close(pipefd[1]);
		//if (dup2(STDIN_FILENO, pipefd[0]) == -1)
		// if (waitpid(pid, NULL, 0) == -1)
		// 	yikes("waitpid() failed", 0);
		if (next && dup2(pipefd[0], STDIN_FILENO) == -1)
			yikes("dup2() failed", 0);
		else if ((waitpid(pid, NULL, 0) == -1))
			;
		close(pipefd[0]);
		//close(pipefd[0]);
	}
	//i gotta rediret output to stdout on last call
}*/

void	executor(t_cmd **lst, char ***ep)
{
	int	i;
	int	next;
	
	if (!lst || !*lst)
	 	return ;
	i = 1;
	if (lst[1] == NULL && lst[0]->builtin)
		lst[0]->builtin(lst[0]->args, ep);
	else
		i = 0;
	while (lst[i])
	{
		next = TRUE;
		if (!lst[i + 1])
			next = FALSE;
		prepare_and_exec(lst[i], *ep, next, i);
		i++;
	}
		
}
