/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:36:02 by yaretel-          #+#    #+#             */
/*   Updated: 2022/11/11 16:31:14 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_check_flag(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd')
		return (c);
	if (c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (c);
	return (0);
}

void	ft_write_flag(char flag, va_list ptr, int *count)
{
	if (flag == 'i' || flag == 'd')
		ft_putint_base(va_arg(ptr, int), "0123456789", count);
	else if (flag == 'x')
		ft_putuint_base(va_arg(ptr, int), "0123456789abcdef", count);
	else if (flag == 'X')
		ft_putuint_base(va_arg(ptr, int), "0123456789ABCDEF", count);
	else if (flag == 'u')
		ft_putuint_base(va_arg(ptr, unsigned int), "0123456789", count);
	else if (flag == 'p')
	{
		ft_putstr("0x", count);
		ft_putul_base(va_arg(ptr, unsigned \
		long int), "0123456789abcdef", count);
	}
	else if (flag == 's')
		ft_putstr(va_arg(ptr, char *), count);
	else if (flag == 'c')
		ft_putchar(va_arg(ptr, int), count);
	else if (flag == '%')
		ft_putchar('%', count);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	char	flag;
	va_list	ptr;
	int		count;

	va_start(ptr, s);
	ft_set2zero(&i, &count);
	while (s[i])
	{
		if (s[i] == '%')
		{
			flag = ft_check_flag(s[i + 1]);
			if (flag)
			{
				ft_write_flag(flag, ptr, &count);
				if (s[i + 1])
					i++;
			}
		}
		else
			ft_putchar(s[i], &count);
		i++;
	}
	va_end(ptr);
	return (count);
}
