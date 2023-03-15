/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:37:36 by yaretel-          #+#    #+#             */
/*   Updated: 2022/10/14 17:10:14 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptrs;

	ptrs = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*(ptrs + i) == (unsigned char)c)
			return ((void *)(ptrs + i));
		i++;
	}
	return (NULL);
}
