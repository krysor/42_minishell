/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:28:30 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/05 15:50:48 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_nb_tokens_before_pipe(t_token *lst_tok);

// Sets default values for all the fields of a a t_cmd struct.
int	set_cmd_default(t_cmd *arr, t_token *token)
{
	int	nb_tokens_before_pipe;
	
	arr->file = NULL;
	arr->builtin = NULL;
	
	//arr->rdr = NULL;//possibly needs correction if contents of rdr struct change
	arr->rdr.type = NULL;
	arr->rdr.file = NULL;
	arr->rdr.next = NULL;
	
	nb_tokens_before_pipe = get_nb_tokens_before_pipe(token);
	//printf("nb_tokens_before_pipe: %d\n", nb_tokens_before_pipe);
	arr->args = malloc(sizeof(char *) * (nb_tokens_before_pipe + 1));
	if (!arr->args)
		return (1);
	arr->args[nb_tokens_before_pipe] = NULL;
	return (0);
}

static int	get_nb_tokens_before_pipe(t_token *lst_tok)
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
	if (!is_operator(token) || !interprete)
		return (0);
	len = ft_strlen(token);
	if (len == 1)
		return (1);
	else if (len == 2
		&& (token[1] == '<' || token[1] == '>'))
		return (1);
	return (0);
}

//decalre a pnt to a pnt one scope outside the loop
void	handle_operator(t_token **lst_tok_pnt, t_cmd *arr)
{	
	t_token	*lst_tok;
	char	*token;
	
	if (!lst_tok_pnt || !*lst_tok_pnt || !arr)
		return ;
	lst_tok = *lst_tok_pnt;
	token = lst_tok->token;
	if (lst_tok->next && (*token == '<' || *token == '>'))
	{
		arr->rdr.type = ft_strdup(token);
		arr->rdr.file = ft_strdup(lst_tok->next->token);
	}
	*lst_tok_pnt = lst_tok->next;
}
