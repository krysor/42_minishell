/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:05 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/13 11:23:57 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	yikes(char *msg, unsigned int ac, ...)
{
	va_list			list;
	unsigned int	i;

	i = 0;
	write(2, msg, ft_strlen(msg));
	va_start(list, ac);
	while (i < ac)
	{
		free(va_arg(list, void *));
		i++;
	}
	va_end(list);
}	

// Checks if input is metacharacter (see bash manual)
char	*is_mchar(char *c)
{
	if (*c == '<' || *c == '>' || *c == '|')
		return (c);
	else if (*c == ' ' || *c == '\t' || *c == '\n')
		return (c);
	else
		return (NULL);
}

// Checks if input is a quote
char	*is_quote(char *c)
{
	if (*c == '\'' || *c == '\"')
		return (c);
	else
		return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
