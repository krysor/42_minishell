/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:39:15 by yaretel-          #+#    #+#             */
/*   Updated: 2022/10/27 16:24:37 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	j = 0;
	while (*(dst + i) && i < size)
		i++;
	while (*(src + j) && i < size - 1)
	{
		*(dst + i) = *(src + j);
		i++;
		j++;
	}
	if (i < size)
		*(dst + i) = '\0';
	return (i - j + ft_strlen(src));
}
