/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:26:04 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/20 18:04:57 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

static void	main_loop(char *line, t_token *lst_tok,
				t_cmd **arr_cmd, char **envp_dup);
static int	process_line(char *line, t_token **lst_tok_pnt,
				t_cmd ***arr_cmd_pnt, char **envp_dup);
static int	execution(t_cmd **arr_cmd, char ***envp_dup_pnt);

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
		free_intermediates(&line, &lst_tok, &arr_cmd);
		signal(SIGQUIT, SIG_IGN);
		line = get_line();
		if (line == NULL && g_exit_code <= 0)
		{			
			g_exit_code *= -1;
			ft_putstr_fd(CMD_EXIT, STDOUT_FILENO);
			break ;
		}
		if (process_line(line, &lst_tok, &arr_cmd, envp_dup))
			continue ;
		if (execution(arr_cmd, &envp_dup))
			break ;
	}
	free_intermediates(&line, &lst_tok, &arr_cmd);
	free_arr(envp_dup);
	dmy_freeall();
}

static int	process_line(char *line, t_token **lst_tok_pnt,
				t_cmd ***arr_cmd_pnt, char **envp_dup)
{
	if (ft_strlen(line) == 0)
		return (1);
	*lst_tok_pnt = lex_it(line, TRUE, NULL);
	*lst_tok_pnt = expander(*lst_tok_pnt, envp_dup);
	*arr_cmd_pnt = parser(*lst_tok_pnt, envp_dup);
	if (*arr_cmd_pnt == NULL)
		return (1);
	signal(SIGINT, &ft_ctrl_c_child);
	handle_redirections(*arr_cmd_pnt);
	if (g_exit_code == INT_MAX)
	{
		g_exit_code = 1;
		return (1);
	}
	return (0);
}

static int	execution(t_cmd **arr_cmd, char ***envp_dup_pnt)
{
	signal(SIGQUIT, &ft_ctrl_slash_child);
	if (arr_cmd && arr_cmd[0] && arr_cmd[1] == NULL
		&& (arr_cmd[0]->builtin == &ft_exit))
	{
		g_exit_code = get_exit_code(arr_cmd[0]->args);
		if (g_exit_code != 256)
			return (1);
		else
			g_exit_code = 1;
	}
	else
		executor(arr_cmd, envp_dup_pnt);
	close_open_fds(arr_cmd);
	return (0);
}

/*
static void	main_loop(char *line, t_token *lst_tok,
			t_cmd **arr_cmd, char **envp_dup)
{
	while (1)
	{
		free_intermediates(&line, &lst_tok, &arr_cmd);
		signal(SIGQUIT, SIG_IGN);
		line = get_line();
		if (line == NULL && g_exit_code <= 0)
		{			
			g_exit_code *= -1;
			ft_putstr_fd(CMD_EXIT, STDOUT_FILENO);
			break ;
		}

		if (ft_strlen(line) == 0)
			continue ;
		lst_tok = lex_it(line, TRUE, NULL);
		lst_tok = expander(lst_tok, envp_dup);
		arr_cmd = parser(lst_tok, envp_dup);
		if (arr_cmd == NULL)
			continue ;
		signal(SIGINT, &ft_ctrl_c_child);
		handle_redirections(arr_cmd);
		if (g_exit_code == INT_MAX)
		{
			g_exit_code = 1;
			continue ;
		}

		if (execution(arr_cmd, &envp_dup))
			break ;
	}
	free_intermediates(&line, &lst_tok, &arr_cmd);
	free_arr(envp_dup);
	dmy_freeall();
}*/

/*
static void	main_loop(char *line, t_token *lst_tok,
			t_cmd **arr_cmd, char **envp_dup)
{
	while (1)
	{
		free_intermediates(&line, &lst_tok, &arr_cmd);
		signal(SIGQUIT, SIG_IGN);
		line = get_line();
		if (line == NULL && g_exit_code <= 0)
		{			
			g_exit_code *= -1;
			ft_putstr_fd(CMD_EXIT, STDOUT_FILENO);
			break ;
		}
		if (ft_strlen(line) == 0)
			continue ;
		lst_tok = lex_it(line, TRUE, NULL);
		lst_tok = expander(lst_tok, envp_dup);
		arr_cmd = parser(lst_tok, envp_dup);
		if (arr_cmd == NULL)
			continue ;
		signal(SIGINT, &ft_ctrl_c_child);
		handle_redirections(arr_cmd);
		if (g_exit_code == INT_MAX)
		{
			g_exit_code = 1;
			continue ;
		}

		signal(SIGQUIT, &ft_ctrl_slash_child);
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
		close_open_fds(arr_cmd);
	}
	free_intermediates(&line, &lst_tok, &arr_cmd);
	free_arr(envp_dup);
	dmy_freeall();
}
*/