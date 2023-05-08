/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:44:18 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/08 09:35:17 by yaretel-         ###   ########.fr       */
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
		dmy_free(va_arg(list, void *));
		i++;
	}
	va_end(list);
}	

char	*is_operator(char *c)
{
	if (*c == '<' || *c == '>' || *c == '|')
		return (c);
	else
		return (NULL);
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

// returns the next occurence of the first argument
char	*find_next(char *s)
{
	char			c;

	if (s == NULL)
		return (NULL);
	c = *s;
	s++;
	while (*s != c)
	{
		if (!(*s))
			return (NULL);
		else
			s++;
	}
	return (s);
}
