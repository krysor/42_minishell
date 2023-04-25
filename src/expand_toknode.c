/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_toknode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:36:53 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/25 12:22:28 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_token(char **envp, size_t newlen, char *tokcod, char *token)
{
	

// TODO rewrite this shit
/*
char	*expand_token(char *token, size_t newlen, char *tokcod, char **envp)
{
	unsigned int	i;
	unsigned int	j;
	char			*new;

	new = malloc(sizeof(*new) * (newlen + 1));
	if (!new)
		yikes("malloc failed\n", 0);
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '$' && !(tokcod[i] == '\''))
			if (!expand_var(new + j, token + i, &j, envp))
				i++;
		else
			new[j++] = token[i++];
	}
	return (new);
}
*/

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

void	expand_toknode(t_token **node, t_token *prev, char *tokcod, char **envp)
{
	char			*expanded;
	char			*expandedtokcod;
	int				expandedlen;
	unsigned int	i;

	if (!is_in_set('$', (*node)->token))
		return ;
	expandedlen = ft_strlen((*node)->token);
	i = 0;
	while ((*node)->token[i])
	{
		if ((*node)->token[i] == '$' && (tokcod[i] != '\''))
			expandedlen += value_len_diff((*node)->token + i, envp);
		i++;
	}
	expanded = expand_token((*node)->token, expandedlen, tokcod, envp);
	expandedtokcod = create_tokcod(expanded);
	free((*node)->token);
	free((*node));
	*node = tokcod_to_list(expanded, expandedtokcod, FALSE, (*node)->next);
	prev->next = *node;
	free(expandedtokcod);
	free(expanded);
}
