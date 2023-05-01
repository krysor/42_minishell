/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:03:35 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/28 17:28:00 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(void)
{
	ft_putstr_fd(MSG_HELLO, 1);
	signal(SIGINT, &ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
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

// int		line_is_not_CMD_EXIT(char *line)
// {
// 	if (ft_strlen(CMD_EXIT) != ft_strlen(line) ||
// 			ft_strncmp(CMD_EXIT, line, ft_strlen(CMD_EXIT)))
// 		return (1);
// 	return (0);
// }

//some freeing required between prompt and line
//if (!prompt)
//	; //SOME KIND OF FREEING REQUIRED HERE
char	*get_line(char **envp)
{
	char	*prompt;
	char	*line;

	prompt = get_prompt(envp);
	line = readline(prompt);
	free(prompt);
	if (!line)
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
	prompt = ft_strjoin(username, "$ ");
	if (!username || !prompt)
		return (NULL);
	return (prompt);
}

void	clean_shell(void)
{
	ft_putstr_fd(CMD_EXIT, 1);
	ft_putchar_fd('\n', 1);
	rl_clear_history();
}
