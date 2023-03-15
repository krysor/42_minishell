/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:18:26 by yaretel-          #+#    #+#             */
/*   Updated: 2022/11/11 16:31:42 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putuint_base(unsigned int nbr, char *base, int *count)
{
	unsigned int	baselen;

	baselen = ft_strlen(base);
	if (ft_base_is_valid(base))
	{
		if (nbr < baselen)
			ft_putchar(base[nbr], count);
		if (nbr >= baselen)
		{
			ft_putint_base(nbr / baselen, base, count);
			ft_putchar(base[nbr % baselen], count);
		}
	}
}
