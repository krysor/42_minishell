/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_switch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:21:49 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/11 12:59:45 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dmy.h"

void	*dmy_action_malloc(t_dmy **lst, size_t size)
{
	void	*new;

	new = malloc(size);
	if (new == NULL)
	{
		perror(NULL);
		return (NULL);	
	}
	if (dmy_lst_add(lst, new) == NULL)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

void	dmy_action_free(t_dmy **lst, void *ptr)
{
	if (dmy_lst_remove(lst, ptr) == 1 && DFREEPROC == 1)
		write(2, "dmy_free() failed, maybe already free'd?\n", 41);
}

void	dmy_action_freeall(t_dmy *lst)
{
	dmy_lst_free(lst);
}

void	*dmy_switch(int action, size_t size, void *ptr)
{
	static t_dmy	*lst = NULL;

	if (action == MALLOC)
		return (dmy_action_malloc(&lst, size));
	if (action == FREEONE)
		dmy_action_free(&lst, ptr);
	if (action == FREEALL)
	{
		dmy_action_freeall(lst);
		lst = NULL;
	}
	return (NULL);
}
