/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:26:04 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/16 13:58:27 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_token		*lst_tok;
	t_cmd		**arr_cmd;
	char		**envp_dup;

	(void)argc;
	(void)argv;
	init_shell();
	line = NULL;
	lst_tok = NULL;
	arr_cmd = NULL;
	envp_dup = arrdup(envp);
	if (!envp_dup)
		return (1);
	while (1)
	{
		free_intermediates(line, lst_tok, arr_cmd);
		line = get_line();
		lst_tok = lex_it(line, TRUE, NULL);
		lst_tok = expander(lst_tok);
		arr_cmd = parser(lst_tok);
		if (arr_cmd && arr_cmd[0] && arr_cmd[1] == NULL
			&& (arr_cmd[0]->builtin == &ft_exit))
			break ;
		executor(arr_cmd, &envp_dup);
	}
	free_intermediates(line, lst_tok, arr_cmd);
	free_arr(envp_dup);
	clean_shell();
	return (0);
}
