/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:26:04 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/13 17:04:55 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

static void	main_loop(char *line, t_token *lst_tok,
				t_cmd **arr_cmd, char **envp_dup);
static void	ft_ctrl_c_child(int i);
static void	ft_ctrl_d_child(int i);

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
	return (g_exit_code);
}

static void	main_loop(char *line, t_token *lst_tok,
			t_cmd **arr_cmd, char **envp_dup)
{
	while (1)
	{
		free_intermediates(line, lst_tok, arr_cmd);
		line = get_line(envp_dup);
		lst_tok = lex_it(line, TRUE, NULL);
		lst_tok = expander(lst_tok, envp_dup);
		arr_cmd = parser(lst_tok, envp_dup);
		signal(SIGINT, &ft_ctrl_c_child);
		signal(SIGQUIT, &ft_ctrl_d_child);
		if (arr_cmd && arr_cmd[0] && arr_cmd[1] == NULL
			&& (arr_cmd[0]->builtin == &ft_exit))
		{
			g_exit_code = get_exit_code(arr_cmd[0]->args);
			if (g_exit_code != 256)
				break ;
			else
				g_exit_code = 1;
		}
		else
			executor(arr_cmd, &envp_dup);
		signal(SIGINT, &ft_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	free_intermediates(line, lst_tok, arr_cmd);
	free_arr(envp_dup);
}

static void	ft_ctrl_c_child(int i)
{
	(void)i;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	ft_ctrl_d_child(int i)
{
	(void)i;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}
