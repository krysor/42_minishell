/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_wrdcod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:57:45 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/20 10:02:49 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mark_words(char *pt, size_t len, char *wrdcod)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		if (!(is_mchar(&pt[i])))
		{
			wrdcod[i] = 'w';
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
// 
// Examples:
// "wwwww.wwwww" == create_wrdcod("hello world");
// "'''''''.wwwww" == create_wrdcod("'hello' world");
// "\"\"\"\"\"\"\"\".wwwwww" == create_wrdcod("\"he'llo\" wor'ld");
char	*create_wrdcod(char *pt)
{
	char			*wrdcod;
	unsigned int	i;
	size_t			len;

	if (!pt)
		yikes("Error: no input in pt during parsing", 0);
	len = ft_strlen(pt);
	wrdcod = malloc(sizeof(*wrdcod) * (len + 1));
	if (wrdcod == NULL)
		yikes("Error: malloc failed", 0);
	i = 0;
	while (i < len)
	{
		wrdcod[i++] = '.';
	}
	wrdcod[i] = '\0';
	mark_words(pt, len, wrdcod);
	mark_quotes(pt, len, wrdcod);
	return (wrdcod);
}
