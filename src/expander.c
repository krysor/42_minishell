/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:06:42 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/08 09:34:41 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*expander(t_token *lst, char **envp)
{
	char	*tokcod;
	t_token	*prev;
	t_token	*first;

	prev = NULL;
	while (lst)
	{
		tokcod = create_tokcod(lst->token);
		expand_toknode(&lst, prev, &tokcod, envp);
		dmy_free(tokcod);
		if (prev == NULL)
			first = lst;
		prev = lst;
		lst = lst->next;
	}
	return (first);
}
