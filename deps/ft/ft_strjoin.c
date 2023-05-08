/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:39:09 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/08 11:19:27 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (*s1 == '\0' && *s2 == '\0')
		return (ft_calloc(1, sizeof(char)));
	ptr = dmy_malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		while (i < ft_strlen(s1))
		{
			*(ptr + i) = *((char *)s1 + i);
			i++;
		}
		*(ptr + i) = *((char *)s2 + i - ft_strlen(s1));
		i++;
	}
	if (ft_strlen(s2) != 0)
		*(ptr + i) = '\0';
	return (ptr);
}
