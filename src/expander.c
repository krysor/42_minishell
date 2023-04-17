/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:06:42 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/16 13:58:32 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*expander(t_token *lst)
{
	char	*tokcod;
	t_token *prev;

	t_token	*first;
	first = lst;
	while (lst)
	{
		tokcod = create_tokcod(lst->token);
		//printf("tokcod before outerquotes: %s\n", tokcod);
		mark_outer_quotes(lst->token, tokcod, -1);
		//printf("tokcod after outerquotes: %s\n", tokcod);
		expand_toknode(&lst, prev, tokcod);
		free(tokcod);
		prev = lst;//possibly this on first call causing error?!!!!
		lst = lst->next;
	}
	return (first);
}
