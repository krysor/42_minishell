/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:06:42 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/27 18:49:52 by yaretel-         ###   ########.fr       */
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
		tokcod = create_tokcod(lst->token);
		puts(tokcod);//remove
		//mark_outer_quotes(lst->token, tokcod, -1);//can go because of restrucutre of expand_toknode
		expand_toknode(&lst, prev, tokcod, envp);
		free(tokcod);
		prev = lst;
		lst = lst->next;
	}
	return (first);
}
