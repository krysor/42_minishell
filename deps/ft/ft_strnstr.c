/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:40:01 by yaretel-          #+#    #+#             */
/*   Updated: 2022/10/14 17:03:43 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		b;
	size_t		l;
	char		*result;

	b = 0;
	l = 0;
	if (*little == '\0')
		return ((char *)big);
	while (b < len && *(big + b) != '\0')
	{
		if (*(big + b) == *(little + l))
			result = ((char *)big + b);
		while (*(big + b) == *(little + l) && b < len)
		{
			if (*(little + l + 1) == '\0')
				return (result);
			b++;
			l++;
		}
		b -= l;
		l = 0;
		b++;
	}
	return (NULL);
}
