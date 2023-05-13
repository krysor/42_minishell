/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:03:35 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/12 18:07:35 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_updated_shlvl(char **envp[]);

int	init_shell(char **envp[])
{
	char	*shlvl;

	g_exit_code = 0;
	ft_putstr_fd(MSG_HELLO, 1);
	signal(SIGINT, &ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
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

//ADD THIS IN INPUTRC file
//echo-control-characters (On)
//	When set to On, on operating systems that indicate they support it,
//		readline echoes a character corresponding
//	to a signal generated from the keyboard.

//bash seems to print ^C on debian but not on macos
void	ft_ctrl_c(int i)
{
	(void)i;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//some freeing required between prompt and line
//if (!prompt)
//	; //SOME KIND OF FREEING REQUIRED HERE
char	*get_line(char **envp)
{
	char	*prompt;
	char	*line;

	prompt = get_prompt(envp);
	line = readline(prompt);
	dmy_free(prompt);
	if (line == NULL)
		line = ft_strdup(CMD_EXIT);
	else
		add_history(line);
	return (line);
}

char	*get_prompt(char **envp)
{
	char	*username;
	char	*prompt;

	username = ft_getenv(envp, "USER");
	prompt = ft_strjoin("BIGmec-sHELL", "$ ");
	if (!username || !prompt)
		return (NULL);
	return (prompt);
}
