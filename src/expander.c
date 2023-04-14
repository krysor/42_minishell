/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:06:42 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/14 11:12:12 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*expander(t_token *lst)
{
	char	*tokcod;
	t_token *prev;

	while (lst)
	{
		tokcod = create_tokcod(lst->token);
		mark_outer_quotes(lst->token, tokcod, -1);
		expand_toknode(&lst, prev, tokcod);
		free(tokcod);
		prev = lst;
		lst = lst->next;
	}
	return (lst);
}
