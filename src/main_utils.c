/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:03:35 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/20 18:34:22 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_updated_shlvl(char **envp[]);

int	init_shell(char **envp[])
{
	char	*shlvl;

	g_exit_code = 0;
	ft_putstr_fd(MSG_HELLO, STDOUT_FILENO);
	shlvl = get_updated_shlvl(envp);
	if (shlvl == NULL || ft_export_var(&shlvl, envp))
	{
		dmy_free(shlvl);
		free_arr(*envp);
		return (1);
	}
	dmy_free(shlvl);
	return (0);
}

static char	*get_updated_shlvl(char **envp[])
{
	char	*s;
	char	*shlvl;
	int		lvl;

	s = ft_getenv(*envp, "SHLVL");
	if (s == NULL)
		shlvl = ft_strdup("SHLVL=1");
	else
	{
		lvl = ft_atoi(s);
		if (lvl <= 0)
			shlvl = ft_strdup("SHLVL=1");
		else
		{
			lvl++;
			if (lvl - 1 > lvl)
				return (NULL);
			s = ft_itoa(lvl);
			shlvl = ft_strjoin("SHLVL=", s);
			dmy_free(s);
		}
	}
	return (shlvl);
}

/*
void	write_readline_to_pipe(int pipefd[2])
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
	{
		line_read = readline("> ");
		write(pipefd[WRITE], " ", 1);
		write(pipefd[WRITE], line_read, ft_strlen(line_read));
		dmy_free(line_trim);
		line_trim = ft_strtrim(line_read, "\f\n\r\t\v ");
		len_line_trim = ft_strlen(line_trim);
		free(line_read);
	}
	dmy_free(line_trim);
	close(pipefd[WRITE]);
	exit(0);
}*/
