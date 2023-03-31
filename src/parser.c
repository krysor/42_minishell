/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:51:12 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/31 14:49:37 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_nb_pipes(t_token *lst_tok);
static void	set_arr(t_cmd **arr, int nb_cmd, t_token **lst_tok_pnt);
static int	set_cmd(t_cmd *arr, t_token **lst_tok_pnt);

t_cmd	**parser(t_token *lst_tok)
{
	int			nb_cmd;
	t_cmd	**arr;
	
	t_token		**lst_tok_pnt;
	lst_tok_pnt = &lst_tok;

	if (!lst_tok)
		return (NULL);
	nb_cmd = get_nb_pipes(lst_tok) + 1;
	arr = malloc(sizeof(t_cmd *) * (nb_cmd + 1));
	if (!arr)
		return (NULL);//some special quitting here?
	arr[nb_cmd] = NULL;
	set_arr(arr, nb_cmd, lst_tok_pnt);
	return (arr);
}

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

int	token_is_pipe(t_token *token)
{
	if (token
		&& token->interprete == TRUE
		&& token->token[0] == '|'
		&& token->token[0] == '\0')
		return (1);
	return (0);
}

static void	set_arr(t_cmd **arr, int nb_cmd, t_token **lst_tok_pnt)
{
	int		i;

	i = 0;
	while (i < nb_cmd)
	{
		arr[i] = malloc(sizeof(t_cmd));
		if (!arr[i] || set_cmd(arr[i], lst_tok_pnt))
			break ;//some freeing necessary here
		i++;
	}
}

static int	set_cmd(t_cmd *arr, t_token **lst_tok_pnt)
{
	int		i;
	
	if (set_cmd_default(arr, *lst_tok_pnt))
		return (1);
	i = 0;
	while (*lst_tok_pnt && !token_is_pipe(*lst_tok_pnt))
	{
		//arr->args[i] = NULL;
		
		//check if meta
		
		if ((*lst_tok_pnt)->interprete && is_token_operator((*lst_tok_pnt)->token))
		 	handle_operator(lst_tok_pnt, arr);
		else
			arr->args[i++] = ft_strdup((*lst_tok_pnt)->token);
		//	if yes look at the next one

		//else check if first
		//	if yes look for file name

		//else add to arg list
		//	to the argv[]
		
		
		// if (token->interprete)
		// 	interprete_token(arr, token);
		// else if (!i)
		// 	set_cmd_file(arr, token);
		// here gotta add statements to fill in all cmd struct elements
		
		(*lst_tok_pnt) = (*lst_tok_pnt)->next;
	}
	arr->args[i] = NULL;
	if ((*lst_tok_pnt) && (*lst_tok_pnt)->next)
		(*lst_tok_pnt) = (*lst_tok_pnt)->next;
	return (0);
}
