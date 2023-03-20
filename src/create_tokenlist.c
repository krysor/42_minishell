/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokenlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:37:19 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/19 16:45:59 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*newtoken(char *token)
{
	t_token	*new;

	if (!token)
		yikes("malloc error\n", 1, token);
	new = malloc(sizeof(*new));
	if (!new)
		yikes("malloc error\n", 1, token);
	new->token = token;
	new->next = NULL;
	return (new);
}

// when given the start of a token in tokcod, it returns the length
// of this token, considering every repeated operation char as one token
size_t	get_tokenlen(char *tokcod)
{
	size_t	i;

	i = 0;
	if (is_operator(tokcod))
		return (cstrlen(tokcod[i], tokcod + i));
	while (tokcod[i] && !is_in_set(tokcod[i], "<>|."))
		i += cstrlen(tokcod[i], tokcod + i);
	return (i);
}

unsigned int	add_token_node(t_token **start, t_token **head, char *pt, char *tokcod, unsigned int i)
{
	size_t	tokenlen;

	tokenlen = get_tokenlen(tokcod + i);
	if (!start || !head || !pt || !tokcod)
	{
		yikes("unexpected NULL pointer\n", 0);
	}
	if (!(*start))
	{
		*start = newtoken(ft_substr(pt, i, tokenlen));
		*head = *start;
	}
	else
	{
		(*head)->next = newtoken(ft_substr(pt, i, tokenlen));
		*head = (*head)->next;
	}
	return (tokenlen);
}

// when given a string and its tokencoding,
// it will give a back a linked list of tokens
t_token	*tokcod_to_list(char *pt, char *tokcod, int interprete, t_token *end)
{
	unsigned int	i;
	t_token			*start;
	t_token			*head;

	i = 0;
	start = NULL;
	while (pt[i] && tokcod[i])
	{
		while (tokcod[i] == '.')
			i++;
		if (!pt[i] || !tokcod[i])
			break ;
		i += add_token_node(&start, &head, pt, tokcod, i);
		head->interprete = interprete;
		head->next = end;
	}
	return (start);
}
