/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:26:04 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/30 17:10:05 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		line_is_not_CMD_EXIT(char *line);
char 	*get_line(void);
char	*get_prompt(void);
void	clean_shell(void);

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
		free_intermediates(line, lst_tok, arr_cmd);

		line = get_line();
		
		lst_tok = lex_it(line, TRUE, NULL);
		print_tokenlist(lst_tok);

		arr_cmd = parser(lst_tok);
		print_arrcmd(arr_cmd);
	}
	free_intermediates(line, lst_tok, arr_cmd);
	clean_shell();
	//system("leaks minishell");
	return (0);
}

