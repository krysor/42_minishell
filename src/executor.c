/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:41:31 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/28 14:25:18 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			oflag|= O_APPEND:
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
}

// opens the file with the right flags and redirects the stdin/stdout accordingly
int		handle_io(char *type, char *arg)
{
	int	fd;

	fd = open(arg, get_oflag(type));
	if (open == -1)
		return (1);
	if (dup2(fd, get_rdr_fd(type)) == -1)
		return (1);
	close(fd);
	return (0);
}

// question: how to dup2() back the default standard output / input
void	prepare_and_exec(t_command *cmd, char *ep[])
{
	t_rdr	*current;
	fd		pipefd[2];
	t_pid	pid;

	if (pipe(pipefd) == -1)
		yikes("pipe failed", 0);
	pid = fork();
	if (pid == -1)
		yikes("fork() failed", 0);
	if (pid = 0)
	{
		close(pipefd[0]);
		if (dup2(STDOUT_FILENO, pipefd[1]) == -1)
			yikes("dup2() failed", 0);
		close(pipefd[1]);
		if (process_redirections(&(cmd->io_rdr)) == -1)
			yikes("processing of redirections failed", 0);
		execve(cmd->file, cmd->args, ep);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(STDIN_FILENO, pipefd[0]) == -1)
			yikes("dup2() failed", 0);
		close(pipefd[0]);
		if (waitpid(pid) == -1)
			yikes("waitpid() failed", 0);
	}
}

void	executor(t_cmd *lst, char *ep[])
{
	while (lst)
	{
		prepare_and_exec(lst, ep);
		lst = lst->next;
	}
}
