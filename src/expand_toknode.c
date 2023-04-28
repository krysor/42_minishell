/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_toknode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:36:53 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/28 10:10:49 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO rewrite this shit
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
		if (token[i] == '$' && !(tokcod[i] == '\'') && expand_var(new + j, token + i, &i, &j, envp) == NULL)
				i++;
		else
			new[j++] = token[i++];
	}
	return (new);
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

int	remove_quotes(char *tokcod, char *varcod, char *pt)
{
	unsigned int	i;

	if (!tokcod || !varcod || !pt)
		return (1);
	if (ft_strlen(tokcod) != ft_strlen(pt) || ft_strlen(pt) != ft_strlen(varcod))
		return (1);
	i = 0;
	while (pt[i])
	{
		if (find_next(is_quote(&pt[i])))
		{
			ft_strtake(pt, i, 1);
}	

/*
void	expand_toknode(t_token **node, t_token *pev, char *tokcod, char **envp)
{
	char	*varcod;

	varcod = create_varcod(tokcod, str);
	if (!varcod)
		yikes("varcod failed", 0);
	remove_quotes(tokcod, varcod, str);
	expand_token(envp, tokcod, str);
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
