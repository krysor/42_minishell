/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:40:06 by yaretel-          #+#    #+#             */
/*   Updated: 2022/10/18 15:15:41 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + len);
	while (i + len >= 0)
	{
		if (s[i + len] == (char)c)
			return ((char *)s + i + len);
		i--;
	}
	return (NULL);
}
