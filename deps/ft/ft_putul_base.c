/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putul_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:18:26 by yaretel-          #+#    #+#             */
/*   Updated: 2022/11/11 16:31:54 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putul_base(unsigned long int nb, char *base, int *count)
{
	unsigned long int	baselen;

	baselen = ft_strlen(base);
	if (ft_base_is_valid(base))
	{
		if (nb < baselen)
		{
			ft_putchar(base[nb], count);
		}
		if (nb >= baselen)
		{
			ft_putul_base(nb / baselen, base, count);
			ft_putchar(base[nb % baselen], count);
		}
	}
}
