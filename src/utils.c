/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:05 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/25 14:36:22 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//commented out because not necessary anymore
/*
char	*strsquash(char x, const char *str)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	count;
	char			*new;

	i = 0;
	count = 0;
	while (str[i])
		if (str[i++] == x)
			count++;
	new = malloc(sizeof(*new) * (i - count + 1));
	if (!new)
		yikes("malloc failed", 0);
	i = 0;
	j = 0;
	while (str[i])
		if (!(str[i++] == x))
			new[j++] = x;
	new[j] = '\0';
	return (new);
}
*/

int	is_in_set(char c, const char *set)
{
	unsigned int	i;

	i = 0;
	if (!set)
		yikes("unexpected NULL pointer\n", 0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

// returns the size of the string
// or until the first occurence of another value than the first argument
size_t	seqstrlen(char *seq, char *s)
{
	size_t	i;

	if (!seq || !s)
		yikes("unexpected NULL pointer\n", 0);
	i = 0;
	while (is_in_set(seq[i], s) && seq[i])
		i++;
	return (i);
}

// returns the size of the string
// or until the first occurence of another value than the first argument
size_t	cstrlen(char c, char *s)
{
	size_t	i;

	if (!s)
		yikes("unexpected NULL pointer\n", 0);
	i = 0;
	while (s[i] == c && s[i])
		i++;
	return (i);
}

// returns the size of the string
// or until any delimeter pointed to by the second argument is found
size_t	strdlen(const char *s, const char *d)
{
	unsigned int	i;

	i = 0;
	if (!s || !d)
		yikes("unexpected NULL pointer\n", 0);
	while (s[i] && !is_in_set(s[i], d))
		i++;
	return (i);
}

char	**arrdup(char **arr)
{
	int		i;
	char	**dup;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
		{
			free_arr(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
