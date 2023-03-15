/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:37:11 by yaretel-          #+#    #+#             */
/*   Updated: 2022/11/01 12:58:26 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*cpy;

	if (lst == NULL)
		return (NULL);
	if (f)
		res = ft_lstnew(f(lst->content));
	else
		return (NULL);
	cpy = res;
	lst = lst->next;
	while (lst)
	{
			cpy->next = ft_lstnew(f(lst->content));
		if (cpy->next == NULL)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		cpy = cpy->next;
		lst = lst->next;
	}
	cpy->next = NULL;
	return (res);
}
