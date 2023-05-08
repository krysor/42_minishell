/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:22:37 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/07 21:31:56 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dmy.h"

// Finds the last node in the list
t_dmy	*dmy_lstlast(t_dmy *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

// Find the node that precedes the node whose 'mem' member matches the 2nd
// argument. In other words: dmy_lstfindprev(lst, find)->next->mem == find
t_dmy	*dmy_lst_findprev(t_dmy *lst, void *find)
{
	if (lst && lst->mem == find)
		return (NULL);
	while (lst)
	{
		if (lst->next && lst->next->mem == find)
			return (lst);
		lst = lst->next;
	}
	return ((void *)1);
}	

// Deletes the next node in the list, or removes the
// first node when second arg is NULL
int	dmy_lst_delnext(t_dmy **lst, t_dmy *prev)
{
	t_dmy	*del;

	if (lst == NULL || *lst == NULL)
		return (1);
	if (prev == NULL)
	{
		del = *lst;
		*lst = (*lst)->next;
		free(del->mem);
		free(del);
	}
	else
	{
		del = prev->next;
		if (del)
		{
			prev->next = del->next;
			free(del->mem);
			free(del);
		}
	}
	return (0);
}
