/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:18:26 by yaretel-          #+#    #+#             */
/*   Updated: 2022/11/11 16:31:35 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_invert(int *count, long *nb)
{
	ft_putchar('-', count);
	*nb = *nb * -1;
}

void	ft_putint_base(int nbr, char *base, int *count)
{
	long	nb;
	int		baselen;

	baselen = ft_strlen(base);
	nb = nbr;
	if (ft_base_is_valid(base))
	{
		if (nb < 0)
			ft_invert(count, &nb);
		if (nb < baselen)
			ft_putchar(base[nb], count);
		if (nb >= baselen)
		{
			ft_putint_base(nb / baselen, base, count);
			ft_putchar(base[nb % baselen], count);
		}
	}
}
