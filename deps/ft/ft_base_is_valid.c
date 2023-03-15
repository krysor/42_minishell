/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_is_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:55:50 by yaretel-          #+#    #+#             */
/*   Updated: 2022/11/11 16:30:51 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_base_is_valid(char *base)
{
	int	i;
	int	j;
	int	once;

	if (ft_strlen(base) == 0 || ft_strlen(base) == 1)
		return (0);
	if (ft_charstr('+', base) == 1 || ft_charstr('-', base) == 1
		|| ft_charstr(' ', base))
		return (0);
	ft_set3zero(&i, &j, &once);
	while (base[i] != '\0')
	{
		while (base[j] != '\0')
		{
			if (base[i] == base[j] && once == 0)
				once = 1;
			else if (base[i] == base[j] && once != 0)
				return (0);
			j++;
		}
		j = 0;
		once = 0;
		i++;
	}
	return (1);
}
