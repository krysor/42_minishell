/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:37:50 by yaretel-          #+#    #+#             */
/*   Updated: 2022/10/14 17:10:35 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptrd;
	char	*ptrs;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (dest);
	ptrs = (char *)src;
	ptrd = (char *)dest;
	i = 0;
	while (i < n)
	{
		*(ptrd + i) = *(ptrs + i);
		i++;
	}
	return (ptrd);
}
