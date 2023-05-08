/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:40:21 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/08 11:19:57 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_toobigstart(void)
{
	char	*ptr;

	ptr = ft_calloc(1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ptr;
	unsigned int	strlen;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_toobigstart());
	strlen = ft_strlen((s + start));
	if (strlen < len)
		len = strlen;
	ptr = dmy_malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = start;
	while (i < len + start)
	{
		*(ptr + i - start) = *(s + i);
		i++;
	}
	*(ptr + i - start) = '\0';
	return (ptr);
}
