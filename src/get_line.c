/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:33:24 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/20 19:05:13 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	write_readline_to_pipe(int pipefd[2]);
static char	*read_line_from_pipe(int pipefd_read);
static void	write_new_readline_to_pipe_and_trim(int pipefd[2],
				char **line_read_pnt, char **line_trim_pnt,
				int *len_lime_trim_pnt);
static void	get_line_from_pipe(pid_t pid, int pipefd[2],
				char **line_pnt, int *exit_status_pnt);

char	*get_line(void)
{
	pid_t	pid;
	int		pipefd[2];
	int		exit_status;
	char	*line;

	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[WRITE]);
		close(pipefd[READ]);
		return (NULL);
	}
	if (pid == 0)
		write_readline_to_pipe(pipefd);
	close(pipefd[WRITE]);
	get_line_from_pipe(pid, pipefd, &line, &exit_status);
	return (line);
}

static void	get_line_from_pipe(pid_t pid, int pipefd[2],
				char **line_pnt, int *exit_status_pnt)
{
	signal(SIGINT, &ft_ctrl_c_main_prompt);
	waitpid(pid, exit_status_pnt, 0);
	signal(SIGINT, &ft_ctrl_c);
	*line_pnt = read_line_from_pipe(pipefd[READ]);
	if (*line_pnt != NULL && ft_strlen(*line_pnt) == ft_strlen(EMPTY_STR)
		&& ft_strncmp(EMPTY_STR, *line_pnt, ft_strlen(EMPTY_STR)) == 0)
	{
		dmy_free(*line_pnt);
		*line_pnt = ft_strdup("");
	}
	else if (*line_pnt != NULL && ft_strlen(*line_pnt) > 0)
		add_history(*line_pnt);
	if (*exit_status_pnt != 0)
	{
		g_exit_code = INT_MAX;
		if (*exit_status_pnt == 256)
		{
			g_exit_code = 1;
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		dmy_free(*line_pnt);
		*line_pnt = NULL;
	}
	else if (*line_pnt == NULL)
		g_exit_code = -g_exit_code;
}

/*
char	*get_line(void)
{
	pid_t	pid;
	int		pipefd[2];
	int		exit_status;
	char	*line;

	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[WRITE]);
		close(pipefd[READ]);
		return (NULL);
	}
	if (pid == 0)
		write_readline_to_pipe(pipefd);
		
	signal(SIGINT, &ft_ctrl_c_main_prompt);
	waitpid(pid, &exit_status, 0);
	signal(SIGINT, &ft_ctrl_c);
	close(pipefd[WRITE]);
	line = read_line_from_pipe(pipefd[READ]);
	if (line != NULL && ft_strncmp(EMPTY_STR, line, ft_strlen(EMPTY_STR)) == 0
		&& ft_strlen(line) == ft_strlen(EMPTY_STR))
	{
		dmy_free(line);
		line = ft_strdup("");
	}
	if (line != NULL)
		add_history(line);
		
	if (exit_status != 0)
	{
		g_exit_code = INT_MAX;
		if (exit_status == 256)
		{
			g_exit_code = 1;
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		dmy_free(line);
		return (NULL);
	}
	if (line == NULL)
		g_exit_code = -g_exit_code;
	return (line);
}*/

static void	write_readline_to_pipe(int pipefd[2])
{
	char	*line_read;
	char	*line_trim;
	int		len_line_trim;

	close(pipefd[READ]);
	signal(SIGINT, &ft_ctrl_c);
	line_read = readline("BIGmec-sHELL$ ");
	signal(SIGINT, &ft_ctrl_c_exit);
	write(pipefd[WRITE], line_read, ft_strlen(line_read));
	if (line_read != NULL && line_read[0] == '\0')
		write(pipefd[WRITE], EMPTY_STR, ft_strlen(EMPTY_STR));
	line_trim = ft_strtrim(line_read, "\f\n\r\t\v ");
	len_line_trim = ft_strlen(line_trim);
	free(line_read);
	while (line_trim != NULL && len_line_trim >= 2
		&& line_trim[len_line_trim - 1] == '|')
		write_new_readline_to_pipe_and_trim(pipefd,
			&line_read, &line_trim, &len_line_trim);
	dmy_free(line_trim);
	close(pipefd[WRITE]);
	dmy_freeall();
	exit(0);
}

static void	write_new_readline_to_pipe_and_trim(int pipefd[2],
			char **line_read_pnt, char **line_trim_pnt, int *len_line_trim_pnt)
{
	*line_read_pnt = readline("> ");
	write(pipefd[WRITE], " ", 1);
	write(pipefd[WRITE], *line_read_pnt, ft_strlen(*line_read_pnt));
	dmy_free(*line_trim_pnt);
	*line_trim_pnt = ft_strtrim(*line_read_pnt, "\f\n\r\t\v ");
	*len_line_trim_pnt = ft_strlen(*line_trim_pnt);
	free(*line_read_pnt);
}

static char	*read_line_from_pipe(int pipefd_read)
{
	char	*full_line;
	char	*full_line_old;
	char	*next_line;
	char	*full_line_trimmed;

	full_line = get_next_line(pipefd_read);
	next_line = get_next_line(pipefd_read);
	while (next_line != NULL)
	{
		full_line_old = full_line;
		full_line = ft_strjoin(full_line_old, next_line);
		dmy_free(full_line_old);
		dmy_free(next_line);
		if (full_line == NULL)
			break ;
		next_line = get_next_line(pipefd_read);
	}
	close(pipefd_read);
	full_line_trimmed = ft_strtrim(full_line, "\f\n\r\t\v ");
	dmy_free(full_line);
	return (full_line_trimmed);
}

/*
static char	*read_line_from_pipe(int pipefd_read)
{
	char	*full_line;
	char	*full_line_old;
	char	*next_line;

	full_line = get_next_line(pipefd_read);
	next_line = get_next_line(pipefd_read);
	while (next_line != NULL)
	{
		full_line_old = full_line;
		full_line = ft_strjoin(full_line_old, next_line);
		dmy_free(full_line_old);
		dmy_free(next_line);
		if (full_line == NULL)
			break ;
		next_line = get_next_line(pipefd_read);
	}
	close(pipefd_read);
	return (full_line);
}*/