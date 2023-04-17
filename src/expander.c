/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:06:42 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/17 10:06:51 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*expander(t_token *lst, char **envp)
{
	char	*tokcod;
	t_token *prev;

	t_token	*first;
	first = lst;
	while (lst)
	{
		//printf("hey\n");
		tokcod = create_tokcod(lst->token);
		mark_outer_quotes(lst->token, tokcod, -1);
		expand_toknode(&lst, prev, tokcod, envp);
		free(tokcod);
		prev = lst;
		lst = lst->next;
	}
	return (first);
}
