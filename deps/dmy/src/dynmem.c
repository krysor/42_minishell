/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynmem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:22:11 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/07 17:38:01 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dmy.h"

void	*dmy_malloc(size_t size)
{
	return (dmy_switch(MALLOC, size, NULL));
}

void	dmy_free(void *ptr)
{
	dmy_switch(FREEONE, 0, ptr);
}

void	dmy_freeall(void)
{
	dmy_switch(FREEALL, 0, NULL);
}
