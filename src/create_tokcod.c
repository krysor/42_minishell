/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokcod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:30:55 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/28 17:26:55 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mark(char *tokcod, unsigned int amount, char marking)
{
	unsigned int	i;

	if (tokcod == NULL)
	{
		return ;
	}
	i = 0;
	while (i < amount)
		tokcod[i++] = marking;
}

void	mark_words_operators(char *pt, size_t len, char *tokcod)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		if (!(is_mchar(&pt[i])))
		{
			tokcod[i] = 'w';
		}
		else if (is_operator(&pt[i]) || pt[i] == '$')
		{
			tokcod[i] = pt[i];
		}
		i++;
	}
}

void	mark_quotes(char *pt, size_t len, char *tokcod)
{
	unsigned int	i;
	char			*cquot;

	i = 0;
	while (i < len)
	{
		if (is_quote(&pt[i]))
		{
			cquot = find_next(is_quote(&pt[i]));
			if (cquot)
			{
				mark(&tokcod[i], cquot - &pt[i] + 1, *is_quote(&pt[i]));
				i += cquot - &pt[i];
			}
		}
		i++;
	}
}

// creates a malloced 'wordcoded' string, which marks the words
// given as an input.
//
// A sequence of 'w' characters represents a 'regular' words 
// A sequence of '\'' characters represents a single quoted word
// A sequence of '"' characters represents a double quoted word
// Unquoted operators remain unchanged
// 
// Examples:
// "wwwww.wwwww.<<.www" == create_tokcod("hello world << EOF");
// "'''''''.wwwww" == create_tokcod("'hello' world");
// "\"\"\"\"\"\"\"\".wwwwww" == create_tokcod("\"he'llo\" wor'ld");
char	*create_tokcod(char *pt)
{
	char			*tokcod;
	unsigned int	i;
	size_t			len;

	if (!pt)
		yikes("Error: no input in pt during parsing", 0);
	len = ft_strlen(pt);
	tokcod = malloc(sizeof(*tokcod) * (len + 1));
	if (tokcod == NULL)
		yikes("Error: malloc failed", 0);
	i = 0;
	while (i < len)
	{
		tokcod[i++] = '.';
	}
	tokcod[i] = '\0';
	mark_words_operators(pt, len, tokcod);
	mark_quotes(pt, len, tokcod);
	return (tokcod);
}
