/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokenlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:37:19 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/14 14:29:25 by yaretel-         ###   ########.fr       */
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
	return (new);
}

t_token	*create_tokenlist(char *pt, char *tokcod)
{
	unsigned int	i;
	t_token			*start;
	t_token			*head;
	size_t			tokenlen;

	i = 0;
	start = NULL;
	while (pt[i] && tokcod[i])
	{
		while (tokcod[i] == '.')
			i++;
		if (!pt[i] || !tokcod[i])
			break ;
		tokenlen = strclen(tokcod + i, '.');
		if (!start)
		{
			start = newtoken(ft_substr(pt, i, tokenlen));
			head = start;
		}
		else
		{
			head->next = newtoken(ft_substr(pt, i, tokenlen));
			head = head->next;
		}
		i += tokenlen;
	}
	return (start);
}
