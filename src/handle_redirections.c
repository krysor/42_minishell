/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:15:35 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/23 12:08:31 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_rdr(t_cmd *cmd, char *type, char *arg);
static int	get_oflag(char *type);
static int	here_doc(char *delimiter, int len_delimiter);
static void	write_readline_to_pipe(int pipefd[2],
				char *delimiter, int len_delimiter);

void	handle_redirections(t_cmd **lst)
{
	int		i;
	t_rdr	*rdr;

	if (lst == NULL)
		return ;
	i = 0;
	while (lst[i])
	{
		rdr = lst[i]->rdr;
		while (rdr)
		{
			handle_rdr(lst[i], rdr->type, rdr->file);
			rdr = rdr->next;
		}
		if (g_exit_code == INT_MAX)
		{
			close_open_fds(lst);
			break ;
		}
		i++;
	}
}

// opens the file with the right flags
//		and redirects the stdin/stdout accordingly
static void	handle_rdr(t_cmd *cmd, char *type, char *file)
{
	int	fd;

	if (ft_strncmp(type, "<<", 3) == 0)
	{
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
		cmd->fd_in = here_doc(file, ft_strlen(file));
		return ;
	}
	fd = open(file, get_oflag(type), 0644);
	if (fd == -1)
	{
		perror(file);
		g_exit_code = INT_MIN;
	}
	else if (*type == '<')
	{
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
		cmd->fd_in = fd;
	}
	else if (*type == '>')
	{
		if (cmd->fd_out >= 0)
			close(cmd->fd_out);
		cmd->fd_out = fd;
	}
}

static int	here_doc(char *delimiter, int len_delimiter)
{
	int		pipefd[2];
	pid_t	pid;
	int		exit_status;

	if (pipe(pipefd) == -1)
	{
		perror(NULL);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		close(pipefd[WRITE]);
		close(pipefd[READ]);
		return (-1);
	}
	if (pid == 0)
		write_readline_to_pipe(pipefd, delimiter, len_delimiter);
	waitpid(pid, &exit_status, 0);
	if (exit_status != 0)
		g_exit_code = INT_MAX;
	close(pipefd[WRITE]);
	return (pipefd[READ]);
}

static void	write_readline_to_pipe(int pipefd[2],
				char *delimiter, int len_delimiter)
{
	char	*next_line;
	int		len_next_line;

	signal(SIGINT, &ft_ctrl_c_exit);
	close(pipefd[READ]);
	next_line = readline("> ");
	len_next_line = ft_strlen(next_line);
	while (next_line && (ft_strncmp(next_line, delimiter, len_delimiter)
			|| len_delimiter != len_next_line) && g_exit_code != INT_MAX)
	{
		if (write(pipefd[WRITE], next_line, len_next_line) == -1)
			perror(NULL);
		if (write(pipefd[WRITE], "\n", 1) == -1)
			perror(NULL);
		free(next_line);
		next_line = readline("> ");
		len_next_line = ft_strlen(next_line);
	}
	if (next_line != NULL)
		free(next_line);
	close(pipefd[WRITE]);
	exit(0);
}

static int	get_oflag(char *type)
{
	int	oflag;

	oflag = 0;
	if (ft_strncmp(type, "<", 2) == 0)
		oflag |= O_RDONLY;
	else if (ft_strncmp(type, ">", 1) == 0)
	{
		oflag |= O_WRONLY | O_CREAT;
		if (ft_strncmp(type, ">>", 3) == 0)
			oflag |= O_APPEND;
		else
			oflag |= O_TRUNC;
	}
	else
		yikes("wrong input for get_oflag\n", 0);
	return (oflag);
}
