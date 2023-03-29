/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:26:04 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/28 15:00:48 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(void);
void	ft_ctrl_c(int i);
void	ft_ctrl_slash(int i);
int		line_is_not_CMD_EXIT(char *line);
char 	*get_line(void);
char	*get_prompt(void);
void	clean_shell(void);
void	free_lst_tok(t_token *lst);

void	free_arr(char **arr);
void	free_arr_argv(t_command **arr_argv);

void	print_tokenlist(t_token *tokenlist_og)
{
	unsigned int	i;
	t_token 		*tokenlist;

	i = 0;
	tokenlist = tokenlist_og;
	while (tokenlist)
	{
		printf("%i)\taddress: %p\ttoken: %s\tinterprete: %i\tnext: %p\n", i, tokenlist, tokenlist->token, tokenlist->interprete, tokenlist->next);
		tokenlist = tokenlist->next;
		i++;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_token		*lst_tok;
	t_command	**arr_cmd;

	(void)argc;
	(void)argv;
	(void)envp;
	init_shell();

	line = NULL;
	lst_tok = NULL;
	arr_cmd = NULL;
	
	while (line_is_not_CMD_EXIT(line))
	{
		free(line);
		free_lst_tok(lst_tok);

		free_arr_argv(arr_cmd);//replace by a function
		//free_arr(arr_cmd);

		line = get_line();
		lst_tok = lex_it(line, TRUE, NULL);
		print_tokenlist(lst_tok);

		arr_cmd = parser(lst_tok);
	}
	free(line);
	free_lst_tok(lst_tok);
	free_arr_argv(arr_cmd);//replace by a function

	clean_shell();
	
	//system("leaks minishell");
	
	return (0);
}

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

void	free_lst_tok(t_token *lst)
{
	t_token	*temp;
	
	while (lst)
	{
		temp = lst->next;
		free(lst->token);
		free(lst);
		lst = temp;
	}
}

void	free_arr_argv(t_command **arr_argv)
{
	int			i;
	t_command	*temp;

	if (!arr_argv)
		return ;
	i = 0;
	while (arr_argv[i])
	{
		temp = arr_argv[i++];
		free(temp->file);
		free_arr(temp->args);//double array free here
		free(temp);	
	}
	free(arr_argv);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}