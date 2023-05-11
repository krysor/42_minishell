/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_rdr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:15:35 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/11 15:38:04 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_rdr(t_cmd *cmd, char *type, char *arg);
static int	get_oflag(char *type);
static int	here_doc(char *delimiter, int len_delimiter);

void	process_redirections(t_cmd *cmd)
{
	t_rdr	*rdr;

	rdr = cmd->rdr;
	while (rdr)
	{
		handle_rdr(cmd, rdr->type, rdr->file);
		rdr = rdr->next;	
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
		perror(NULL);
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
	char	*next_line;
	int		len_next_line;

	if (pipe(pipefd) == -1)
	{
		perror(NULL);
		return (-1);	
	}
	next_line = get_next_line(0);
	len_next_line = ft_strlen(next_line);
	while (next_line && (ft_strncmp(next_line, delimiter, len_delimiter)
			|| len_delimiter != len_next_line - 1))
	{
		if (write(pipefd[WRITE], next_line, len_next_line) == -1)
			perror(NULL);
		free(next_line);
		next_line = get_next_line(0);	
		len_next_line = ft_strlen(next_line);
	}
	if (next_line)
		free(next_line);
	close(pipefd[WRITE]);
	return (pipefd[READ]);
}


/*
static void	handle_rdr(t_cmd *cmd, char *type, char *file)
{
	int	fd;
	int	pipefd[2];

	if (ft_strncmp(type, "<<", 3) == 0)
	{
		if (pipe(pipefd) == -1)
			perror(NULL);
		else
			cmd->fd_in = here_doc(pipefd, file);
		return ;
	}
	fd = open(file, get_oflag(type), 0644);
	if (fd == -1)
		perror(NULL);
	else if (*type == '>')
	{
		if (cmd->fd_out >= 0)
			close(cmd->fd_out);
		cmd->fd_out = fd;
	}
	else
	{
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
		cmd->fd_in = fd;
	}
}

static int	here_doc(int pipefd[], char *delimiter)
{
	char	*next_line;
	int		len_delimiter;
	int		len_next_line;

	len_delimiter = ft_strlen(delimiter);
	next_line = get_next_line(0);
	len_next_line = ft_strlen(next_line);
	while (next_line && (ft_strncmp(next_line, delimiter, len_delimiter)
			|| len_delimiter != len_next_line - 1))
	{
		if (write(pipefd[WRITE], next_line, len_next_line) == -1)
			perror("write: temp");
		free(next_line);
		next_line = get_next_line(0);	
		len_next_line = ft_strlen(next_line);
	}
	if (next_line)
		free(next_line);
	close(pipefd[WRITE]);
	return (pipefd[READ]);
}*/

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
