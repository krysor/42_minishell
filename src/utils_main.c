/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:03:35 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/30 17:05:14 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(void)
{
	ft_putstr_fd(MSG_HELLO, 1);
	signal(SIGINT, &ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	//ADD THIS IN INPUTRC file
	//echo-control-characters (On)
     //         When set to On, on operating systems that indicate they support it, readline echoes a character corresponding
       //       to a signal generated from the keyboard.
}

//bash seems to print ^C on debian but not on macos
void	ft_ctrl_c(int i)
{
	(void)i;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();//Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. 
	rl_replace_line("", 0);//Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared. 
	rl_redisplay();//Change what’s displayed on the screen to reflect the current contents of rl_line_buffer. 
}

int		line_is_not_CMD_EXIT(char *line)
{
	if (ft_strlen(CMD_EXIT) != ft_strlen(line) ||
			ft_strncmp(CMD_EXIT, line, ft_strlen(CMD_EXIT)))
		return (1);
	return (0);
}

char *get_line(void)
{
	char	*prompt;
	char	*line;

	prompt = get_prompt();
	//if (!prompt)
	//	; //SOME KIND OF FREEING REQUIRED HERE
	line = readline(prompt);
	free(prompt);
	if (!line)
		line = ft_strdup(CMD_EXIT);//This happens when 1)CTRL+D on empty line & 2)malloc inside readline fails
	else
		add_history(line);
	return (line);
}

char	*get_prompt(void)
{
	char *username;
	char *prompt;

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