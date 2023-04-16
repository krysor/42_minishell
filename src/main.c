/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:26:04 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/14 14:29:07 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		line_is_not_CMD_EXIT(char *line);
char 	*get_line(void);
char	*get_prompt(void);
void	clean_shell(void);

void	print_arr(char **arr);

char	**arrdup(char **arr);

int main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_token		*lst_tok;
	t_cmd		**arr_cmd;
	char		**envp_dup;

	// print_arr(envp);

	(void)argc;
	(void)argv;
	(void)envp;
	
	init_shell();
	line = NULL;
	
	lst_tok = NULL;
	arr_cmd = NULL;

	envp_dup = arrdup(envp);
	if (!envp_dup)
		return (1); //or some other errno

	while (1)
	{
		free_intermediates(line, lst_tok, arr_cmd);

		line = get_line();
		
		lst_tok = lex_it(line, TRUE, NULL);
		//print_tokenlist(lst_tok);

		arr_cmd = parser(lst_tok);
		//print_arrcmd(arr_cmd);

		if (arr_cmd && arr_cmd[0] && arr_cmd[1] == NULL
			&& (arr_cmd[0]->builtin == &ft_exit))
			break ;
		executor(arr_cmd, &envp_dup);
	}
	//use arr_cmd[0] to set errno
	free_intermediates(line, lst_tok, arr_cmd);
	free_arr(envp_dup);
	
	clean_shell();


	//system("leaks minishell");
	return (0); //return errno instead
}

// void	print_arr(char **arr)
// {
// 	int	i;
	
// 	if (!arr)
// 		return ;
// 	i = 0;
// 	while (arr[i])
// 		printf("%s\n", arr[i++]);
// }


char	**arrdup(char **arr)
{
	int		i;
	char	**dup;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
		{
			free_arr(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

