/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:36:20 by yaretel-          #+#    #+#             */
/*   Updated: 2022/10/13 16:36:21 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_min2147483648toa(void)
{
	char	*ptr;

	ptr = ft_calloc(12, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, "-2147483648", 12);
	return (ptr);
}

static int	ft_getsize(int n, int *neg)
{
	int	size;

	size = 1;
	if (n < 0)
	{
		n = n * -1;
		*neg = 1;
		size++;
	}
	while (n >= 10)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	int		neg;
	char	*ptr;
	int		i;

	if (n == -2147483648LL)
		return (ft_min2147483648toa());
	neg = 0;
	size = ft_getsize(n, &neg);
	ptr = ft_calloc(size + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (neg == 1)
	{
		*ptr = '-';
		n = n * -1;
	}
	i = size - 1;
	while (i >= neg)
	{
		*(ptr + i) = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (ptr);
}
