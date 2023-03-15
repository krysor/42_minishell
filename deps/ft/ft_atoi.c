/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:33:44 by yaretel-          #+#    #+#             */
/*   Updated: 2022/10/25 14:37:26 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_convert(int i, int sign, const char *str)
{
	unsigned long int	result;
	int					count;

	result = 0;
	count = 0;
	while (str[i] == '0')
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		result = (result * 10) + (str[i] - 48);
		count++;
		if ((result > (unsigned long int)LONG_MAX || count > 19) && sign == -1)
			return (0);
		else if ((result > (unsigned long int)LONG_MAX
				|| count > 19) && sign == 1)
			return (-1);
		i++;
	}
	return ((int)result);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	base;
	int	i;

	i = 0;
	base = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (ft_isdigit(str[i]) == 1)
	{
		base = ft_convert(i, sign, str);
		return (base * sign);
	}
	else
		return (0);
}
