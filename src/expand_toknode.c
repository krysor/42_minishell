/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_toknode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:36:53 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/28 17:46:32 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO rewrite this shit
char	*expand_token(char **envp, char *tokcod, char **token)
{
	unsigned int	i;
	char			*current_key;
	char			*current_value;
	size_t			keylen;

	i = 0;
	while ((*token)[i])
	{
		if ((*token)[i] == '$' || tokcod[i] != '\'')
		{
			keylen = strdlen(&(*token)[i], " \t\n|<>\"\'") + 1;
			current_key = malloc(sizeof(*current_key) * keylen + 1);
			if (!current_key)
				return (NULL);
			ft_strlcpy(current_key, &(*token)[i], keylen + 1);
			current_value = ft_getenv(envp, current_key);
			free(current_key);
			ft_strtake(token, i, keylen);
			ft_strins(*token, i, current_value);
		}
	}
	return (*token);
}

// find a quote pair and replaces the quote chars with marking'
void	mark_outer_quotes(char *pt, char *tokcod, char marking)
{
	unsigned int	i;
	char			*next;

	i = 0;
	while (pt[i])
	{
		if (!(pt[i] == marking))
		{
			next = find_next(is_quote(pt + i));
			if (is_quote(pt + i) && next)
			{
				pt[i] = marking;
				*next = marking;
				(tokcod)[i] = marking;
				tokcod[next - &pt[i]] = marking;
			}
		}
		i++;
	}
}

//commented out because not necessary anymore
/*
void	remove_quotes(char **pt, char **tokcod)
{
	char			*new_pt;
	char			*new_tokcod;

	mark_outer_quotes(*pt, *tokcod, '\24');
	new_pt = strsquash('\24', *pt);
	new_tokcod = strsquash('\24', *tokcod);
	free(*pt);
	free(*tokcod);
	*pt = new_pt;
	*tokcod = new_tokcod;
}
*/

/* (MAYBE UNNECCESARY)
// you give a token coding (tokcod) and the input string of the prompt (pt) 
// gives back a variable coding on which you can tell which characters should be expanded
// a result of "..$.." tells to expand at the character at index 2
char	*create_varcod(char *tokcod, char *pt)
{
	size_t			len;
	char			*varcod;
	unsigned int	i;

	if (!pt || !tokcod)
		return (NULL);
	len = ft_strlen(pt);
	if (len != ft_strlen(tokcod))
		return (NULL);
	varcod = malloc(sizeof(*varcod) * (len + 1));
	i = 0;
	while (i < len)
		varcod[i++] = '.';
	varcod[i] = '\0';
	i = 0;
	while (i < len)
	{
		if (pt[i] == '$' && tokcod[i] != '\'')
			varcod[i] = '$';
		i++;
	}
	return (varcod);
}
*/

int	remove_quotes(char **tokcod, char **pt)
{
	unsigned int	i;
	size_t			distance;

	if (!(*tokcod) || !(*pt))
		return (1);
	if (ft_strlen((*tokcod)) != ft_strlen((*pt)))
		return (1);
	i = 0;
	while ((*pt)[i])
	{
		if (find_next(is_quote(&(*pt)[i])))
		{
			distance = find_next(&(*pt)[i]) - &(*pt)[i];
			ft_strtake(pt, i, 1);
			ft_strtake(pt, i + distance - 1, 1);
			ft_strtake(tokcod, i, 1);
			ft_strtake(tokcod, i + distance - 1, 1);
		}
		else
			i++;
	}
	return (0);
}

void	expand_toknode(t_token **node, t_token *pev, char *tokcod, char **envp)
{
	(void)pev;
	if (remove_quotes(&tokcod, &((*node)->token)))
		yikes("invalid input for remove quotes", 0);
	expand_token(envp, tokcod, &((*node)->token));
}
