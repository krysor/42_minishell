/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:28:30 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/20 16:36:36 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Returns the number of pipe metacharacters found in the t_token list.
int	get_nb_pipes(t_token *lst_tok)
{
	int		nb_pipes;
	int		prev_is_pipe;
	t_token	*temp;

	nb_pipes = 0;
	prev_is_pipe = FALSE;
	temp = lst_tok;
	while (temp)
	{
		if (token_is_pipe(temp))
		{
			if (prev_is_pipe == FALSE && temp->next != NULL
				&& token_is_pipe(temp->next) == FALSE)
			{
				nb_pipes++;
				prev_is_pipe = TRUE;
			}
			else
				return (INT_MIN);
		}
		else
			prev_is_pipe = FALSE;
		temp = temp->next;
	}
	return (nb_pipes);
}

// Returns 1 in case a given t_token is a to be interpreted pipe.
// Otherwise returns 0.
int	token_is_pipe(t_token *token)
{
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
	if (lst_tok->next == NULL || token_is_operator(lst_tok->next) == TRUE)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		if (lst_tok->next == NULL)
			ft_putstr_fd("newline", STDERR_FILENO);
		else
			ft_putstr_fd(lst_tok->next->token, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		g_exit_code = 258;
		return (1);
	}
	rdr = rdr_new(token, lst_tok->next->token);
	if (rdr == NULL)
		return (2);
	lst_rdr_add(&arr->rdr, rdr);
	*lst_tok_pnt = lst_tok->next;
	return (0);
}
