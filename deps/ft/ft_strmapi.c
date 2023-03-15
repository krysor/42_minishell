/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:39:38 by yaretel-          #+#    #+#             */
/*   Updated: 2022/10/13 16:39:49 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		slen;
	char	*res;

	if (s == NULL || f == NULL)
		return (NULL);
	slen = ft_strlen(s);
	i = 0;
	res = ft_calloc(slen + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < slen)
	{
		*(res + i) = f(i, *(s + i));
		i++;
	}
	return (res);
}
