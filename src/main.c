/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:26:04 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/08 11:31:30 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_exit(t_cmd **arr_cmd);

//add protections after or inside each function?
//replace with global var
void	main_loop(char *line, t_token *lst_tok,
			t_cmd **arr_cmd, char **envp_dup)
{
	int	err_no_local;

	while (1)
	{
		free_intermediates(line, lst_tok, arr_cmd);
		line = get_line(envp_dup);
		lst_tok = expander(lex_it(line, TRUE, NULL), envp_dup);
		arr_cmd = parser(lst_tok, envp_dup);
		if (arr_cmd && arr_cmd[0] && arr_cmd[1] == NULL
			&& (arr_cmd[0]->builtin == &ft_exit))
		{
			err_no_local = get_exit_code(arr_cmd[0]->args);
			if (err_no_local != 256)
				break ;
			else
				err_no_local = 1;
		}
		else
			executor(arr_cmd, &envp_dup);
	}
	free_intermediates(line, lst_tok, arr_cmd);
	free_arr(envp_dup);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_token		*lst_tok;
	t_cmd		**arr_cmd;
	char		**envp_dup;

	(void)argc;
	(void)argv;
	line = NULL;
	lst_tok = NULL;
	arr_cmd = NULL;
	envp_dup = arrdup(envp);
	if (envp_dup == NULL)
		return (1);
	if (init_shell(&envp_dup))
		return (2);
	main_loop(line, lst_tok, arr_cmd, envp_dup);
	rl_clear_history();
	//system("leaks minishell");
	return (0);
}

/*
int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_token		*lst_tok;
	t_cmd		**arr_cmd;
	char		**envp_dup;

	(void)argc;
	(void)argv;
	(void)envp;
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
		line = get_line(envp);
		lst_tok = lex_it(line, TRUE, NULL);
		
		lst_tok = expander(lst_tok, envp_dup);

		arr_cmd = parser(lst_tok, envp_dup);

		if (arr_cmd && arr_cmd[0] && arr_cmd[1] == NULL
			&& (arr_cmd[0]->builtin == &ft_exit))
			break ;
		executor(arr_cmd, &envp_dup);
	}
	free_intermediates(line, lst_tok, arr_cmd);
	free_arr(envp_dup);
	clean_shell();
	return (0);
}*/

// void	print_arr(char **arr)
// {
// 	int	i;

// 	if (!arr)
// 		return ;
// 	i = 0;
// 	while (arr[i])
// 		printf("%s\n", arr[i++]);
// }
