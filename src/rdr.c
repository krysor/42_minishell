/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:28:30 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/08 09:35:13 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_rdr	*rdr_new(char *type, char *file)
{
	t_rdr	*rdr;

	rdr = dmy_malloc(sizeof(t_rdr));
	if (!rdr)
		return (NULL);
	rdr->type = ft_strdup(type);
	rdr->file = ft_strdup(file);
	if (!rdr->type || !rdr->file)
	{
		dmy_free(rdr->type);
		dmy_free(rdr->file);
		dmy_free(rdr);
		return (NULL);
	}
	rdr->next = NULL;
	return (rdr);
}

t_rdr	*lst_rdr_last(t_rdr *lst_rdr)
{
	t_rdr	*temp;

	if (!lst_rdr)
		return (NULL);
	temp = lst_rdr;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	lst_rdr_add(t_rdr **lst_rdr_pnt, t_rdr *rdr)
{
	if (!rdr || !lst_rdr_pnt)
		return ;
	if (!*lst_rdr_pnt)
		*lst_rdr_pnt = rdr;
	else
		lst_rdr_last(*lst_rdr_pnt)->next = rdr;
}
