/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:22:29 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/07 21:32:28 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dmy.h"

// adds a new node at the end of the list with its 'mem' member
// set to the second argument
t_dmy	*dmy_lst_add(t_dmy **lst, void *mem)
{
	t_dmy	*new;

	if (lst == NULL || mem == NULL)
		return (NULL);
	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->mem = mem;
	if (*lst == NULL)
		*lst = new;
	else
		dmy_lstlast(*lst)->next = new;
	return (new);
}

// removes the node from the list whose 'mem' member matches the second argument
int	dmy_lst_remove(t_dmy **lst, void *remove)
{
	t_dmy	*prev;

	prev = dmy_lst_findprev(*lst, remove);
	if (prev == (void *)1)
		return (1);
	if (dmy_lst_delnext(lst, prev) == 1)
		return (1);
	return (0);
}

// delete the entire list
void	dmy_lst_free(t_dmy *lst)
{
	t_dmy	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->mem);
		free(lst);
		lst = next;
	}
}
