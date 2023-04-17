/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:03:35 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/12 17:56:14 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(void)
{
	ft_putstr_fd(MSG_HELLO, 1);
	signal(SIGINT, &ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

//bash seems to print ^C on debian but not on macos
void	ft_ctrl_c(int i)
{
	(void)i;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*get_line(void)
{
	char	*prompt;
	char	*line;

	prompt = get_prompt();
	line = readline(prompt);
	free(prompt);
	if (!line)
		line = ft_strdup(CMD_EXIT);
	else
		add_history(line);
	return (line);
}

char	*get_prompt(void)
{
	char	*username;
	char	*prompt;

	username = getenv("USER");
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
