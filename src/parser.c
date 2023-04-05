/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:51:12 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/05 15:50:28 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_nb_pipes(t_token *lst_tok);
static int	set_arr(t_cmd **arr, int nb_cmd, t_token **lst_tok_pnt);
static int	set_cmd(t_cmd *arr, t_token **lst_tok_pnt);

// Allocates, sets and returns a pointer to an array of t_cmd structs.
// Size is equal to 1 + the number of commands found in the t_token list.
// In case of an error it returns NULL.
t_cmd	**parser(t_token *lst_tok)
{
	int		nb_cmd;
	t_token	**lst_tok_pnt;
	t_cmd	**arr;

	if (!lst_tok)
		return (NULL);
	nb_cmd = get_nb_pipes(lst_tok) + 1;
	arr = malloc(sizeof(t_cmd *) * (nb_cmd + 1));
	if (!arr)
		return (NULL);//some special quitting here?
	arr[nb_cmd] = NULL;
	lst_tok_pnt = &lst_tok;
	if (set_arr(arr, nb_cmd, lst_tok_pnt))
		free_arr_argv(arr);//not sure if this way of freeing works
	return (arr);
}

// Returns the number of pipe metacharacters found in the t_token list.
static int	get_nb_pipes(t_token *lst_tok)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = lst_tok;
	while (temp)
	{
		if (token_is_pipe(temp))
			i++;
		temp = temp->next;
	}
	return (i);
}

// Returns 1 in case a given t_token is a to be interpreted pipe.
// Otherwise returns 0.
int	token_is_pipe(t_token *token)
{
	if (token
		&& token->interprete == TRUE
		&& token->token[0] == '|'
		&& token->token[1] == '\0')
		return (1);
	return (0);
}

// Allocates and sets the elements of a t_cmd struct array.
// Returns 1 in case of an error and 0 on success.
static int	set_arr(t_cmd **arr, int nb_cmd, t_token **lst_tok_pnt)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		arr[i] = malloc(sizeof(t_cmd));
		if (!arr[i]) 
			return (1);//not sure if it would segfault
		if (set_cmd(arr[i], lst_tok_pnt))
			return (1);//not sure if it would segfault
		i++;
	}
	return (0);
}

// Allocates and sets a single t_cmd struct element.
// Firstly it sets default values to all the variables of the element.
// Then it iterates over a t_token list saving all it's token values as fields
// 		until it reaches a to be interpreted pipe. This signals beginning of next command.
// Returns 1 in case of an error and 0 on success.
static int	set_cmd(t_cmd *arr, t_token **lst_tok_pnt)
{
	int		i;
	t_token	*lst_tok;
	
	lst_tok = *lst_tok_pnt;
	if (set_cmd_default(arr, lst_tok))
		return (1);
	if (token_is_pipe(lst_tok) && lst_tok->next)
		lst_tok = lst_tok->next;
	i = 0;
	while (lst_tok && !token_is_pipe(lst_tok))
	{
		if (token_is_operator(lst_tok))
			handle_operator(&lst_tok, arr);
		else
			arr->args[i++] = ft_strdup(lst_tok->token);
		lst_tok = lst_tok->next;
	}
	*lst_tok_pnt = lst_tok;
	arr->args[i] = NULL;
	return (0);
}
