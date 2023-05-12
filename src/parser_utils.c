/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:28:30 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/11 16:52:13 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Returns the number of pipe metacharacters found in the t_token list.
int	get_nb_pipes(t_token *lst_tok)
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
	//printf("token:\n");
	
	if (token != NULL
		&& token->interprete == TRUE
		&& token->token != NULL
		&& token->token[0] == '|'
		&& token->token[1] == '\0')
		return (1);
	return (0);
}

int	get_nb_tokens_before_pipe(t_token *lst_tok)
{
	int		nb;
	t_token	*temp;

	nb = 0;
	temp = lst_tok;
	while (temp && !token_is_pipe(temp))
	{
		nb++;
		temp = temp->next;
	}
	return (nb);
}

int	token_is_operator(t_token *lst_tok)
{
	int		len;
	char	*token;

	token = lst_tok->token;
	if (is_operator(token) == NULL || lst_tok->interprete == FALSE)
		return (FALSE);
	len = ft_strlen(token);
	if (len == 1)
		return (TRUE);
	else if (len == 2
		&& (token[1] == '<' || token[1] == '>'))
		return (TRUE);
	return (FALSE);
}

//decalre a pnt to a pnt one scope outside the loop
int	handle_operator(t_token **lst_tok_pnt, t_cmd *arr)
{	
	t_token	*lst_tok;
	char	*token;
	t_rdr	*rdr;

	if (!lst_tok_pnt || !*lst_tok_pnt || !arr)
		return (1);
	lst_tok = *lst_tok_pnt;
	token = lst_tok->token;
	if (lst_tok->next && (*token == '<' || *token == '>'))
	{
		rdr = rdr_new(token, lst_tok->next->token);
		if (!rdr)
			return (1);
		lst_rdr_add(&arr->rdr, rdr);
	}
	*lst_tok_pnt = lst_tok->next;
	return (0);
}
