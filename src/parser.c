/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:51:12 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/20 18:05:41 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	set_arr(t_cmd **arr, int nb_cmd,
				t_token **lst_tok_pnt, char **envp);
static int	set_cmd(t_cmd *arr, t_token **lst_tok_pnt, char **envp);
static int	set_cmd_default(t_cmd *arr, t_token *token);
static int	update_cmd(t_token **lst_tok_pnt,
				t_token *lst_tok, t_cmd *cmd, char **envp);

// Allocates, sets and returns a pointer to an array of t_cmd structs.
// Size is equal to 1 + the number of commands found in the t_token list.
// In case of an error it returns NULL.
t_cmd	**parser(t_token *lst_tok, char **envp)
{
	int		nb_cmd;
	t_token	**lst_tok_pnt;
	t_cmd	**arr;

	if (lst_tok == NULL)
		return (NULL);
	nb_cmd = get_nb_pipes(lst_tok) + 1;
	if (invalid_nb_cmd(nb_cmd))
		return (NULL);
	arr = dmy_malloc(sizeof(t_cmd *) * (nb_cmd + 1));
	if (arr == NULL)
		return (NULL);
	arr[nb_cmd] = NULL;
	lst_tok_pnt = &lst_tok;
	if (set_arr(arr, nb_cmd, lst_tok_pnt, envp))
	{	
		free_arr_argv(arr);
		return (NULL);
	}
	return (arr);
}

// Allocates and sets the elements of a t_cmd struct array.
// Returns 1 in case of an error and 0 on success.
static int	set_arr(t_cmd **arr, int nb_cmd, t_token **lst_tok_pnt, char **envp)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
		arr[i++] = NULL;
	i = 0;
	while (i < nb_cmd)
	{
		arr[i] = dmy_malloc(sizeof(t_cmd));
		if (arr[i] == NULL)
			return (1);
		if (set_cmd(arr[i], lst_tok_pnt, envp))
			return (1);
		i++;
	}
	return (0);
}

// Allocates and sets a single t_cmd struct element.
// Firstly it sets default values to all the variables of the element.
// Secondly it iterates over a t_token list and saves all it's token values
//		as fields until it reaches a to be interpreted pipe.
//		This signals beginning of next command.
// Returns 1 in case of an error and 0 on success.
static int	set_cmd(t_cmd *cmd, t_token **lst_tok_pnt, char **envp)
{
	t_token	*lst_tok;

	if (lst_tok_pnt == NULL)
		return (1);
	lst_tok = *lst_tok_pnt;
	if (token_is_pipe(lst_tok) && lst_tok->next)
		lst_tok = lst_tok->next;
	if (set_cmd_default(cmd, lst_tok))
		return (1);
	if (update_cmd(lst_tok_pnt, lst_tok, cmd, envp))
		return (1);
	return (0);
}

// Sets default values for all the fields of a a t_cmd struct.
static int	set_cmd_default(t_cmd *arr, t_token *token)
{
	int	nb_tokens_before_pipe;
	int	i;

	arr->rdr = NULL;
	arr->file = NULL;
	arr->builtin = NULL;
	nb_tokens_before_pipe = get_nb_tokens_before_pipe(token);
	arr->args = dmy_malloc(sizeof(char *) * (nb_tokens_before_pipe + 1));
	if (arr->args == NULL)
		return (1);
	i = 0;
	while (i <= nb_tokens_before_pipe)
		arr->args[i++] = NULL;
	arr->fd_in = -2;
	arr->fd_out = -2;
	return (0);
}

/*
// Sets default values for all the fields of a a t_cmd struct.
static int	set_cmd_default(t_cmd *arr, t_token *token)
{
	int	nb_tokens_before_pipe;

	arr->rdr = NULL;
	arr->file = NULL;
	arr->builtin = NULL;
	nb_tokens_before_pipe = get_nb_tokens_before_pipe(token);
	arr->args = dmy_malloc(sizeof(char *) * (nb_tokens_before_pipe + 1));
	if (arr->args == NULL)
		return (1);
	arr->args[nb_tokens_before_pipe] = NULL;
	arr->fd_in = -2;
	arr->fd_out = -2;
	return (0);
}*/

static int	update_cmd(t_token **lst_tok_pnt, t_token *lst_tok,
						t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	while (lst_tok && token_is_pipe(lst_tok) == FALSE)
	{
		if (token_is_operator(lst_tok) == TRUE)
		{
			if (handle_operator(&lst_tok, cmd))
				return (1);
		}
		else
		{
			cmd->args[i] = ft_strdup(lst_tok->token);
			if (cmd->args[i] == NULL)
				return (1);
			i++;
		}
		if (lst_tok != NULL)
			lst_tok = lst_tok->next;
	}
	*lst_tok_pnt = lst_tok;
	if (cmd->args[0] != NULL && set_cmd_builtin(cmd))
		cmd->file = get_path(cmd->args[0], envp);
	return (0);
}
