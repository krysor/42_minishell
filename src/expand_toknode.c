/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_toknode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:36:53 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/23 11:26:59 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	attempt_expansion(char **envp, char **tokcod, char **token, unsigned int *i)
{
	char			*ck;
	char			*cv;
	size_t			keylen;
	int				dollar_questionmark;

	dollar_questionmark = 0;
	keylen = get_keylen(tokcod, token, i);
	ck = dmy_malloc(sizeof(*ck) * (keylen + 1));
	if (!ck)
		return (1);
	ft_strlcpy(ck, &(*token)[*i + 1], keylen + 1);
	cv = ft_getenv(envp, ck);
	if ((*token)[*i + 1] == '?' && (*token)[*i + 2] == '\0')
	{
		cv = ft_itoa(g_exit_code);
		dollar_questionmark = 1;
	}
	ft_strtake(token, *i, keylen + 1 + dollar_questionmark);
	ft_strins(token, *i, cv);
	tokcodadjust(tokcod, *i, ft_strlen(cv) - ft_strlen(ck));
	dmy_free(ck);
	*i += ft_strlen(cv);
	dmy_free(cv);
	return (0);
}

// cv == current value
// ck == current key
char	*expand_token(char **envp, char **tokcod, char **token)
{
	unsigned int	i;

	i = 0;
	if (ft_strlen(*tokcod) != ft_strlen(*token))
		return (NULL);
	while ((*token)[i])
	{
		if ((*token)[i] == '$' && (*tokcod)[i] != '\'' &&
			!is_mchar(&(*token)[i + 1]) && (*token)[i + 1] != '\0')
		{
			if (attempt_expansion(envp, tokcod, token, &i) == 1)
				return (NULL);
		}
		else
			i++;
	}
	return (*token);
}

static void	ft_strtake_combo(char **pt, unsigned int i,
				size_t distance, char **tokcod)
{
	ft_strtake(pt, i, 1);
	ft_strtake(pt, i + distance - 2, 1);
	ft_strtake(tokcod, i, 1);
	ft_strtake(tokcod, i + distance - 2, 1);
}

int	remove_quotes(char **tokcod, char **pt)
{
	unsigned int	i;
	size_t			distance;

	if (!(*tokcod) || !(*pt))
		return (1);
	if (ft_strlen((*tokcod)) != ft_strlen((*pt)))
		return (1);
	i = strdlen(*tokcod, "\'\"");
	while ((*tokcod)[i])
	{
		if (is_in_set((*tokcod)[i], "\'\""))
		{
			distance = cstrlen((*tokcod)[i], &(*tokcod)[i]);
			if (distance < 2)
			{
				write(2, ERR_MSG_RM_QUOTES, ERR_MSG_RM_QUOTES_COUNT);
				return (1);
			}
			ft_strtake_combo(pt, i, distance, tokcod);
			i += distance - 2;
		}
		else
			i++;
	}
	return (0);
}

void	expand_toknode(t_token **node, t_token *pev, char **tokcod, char **envp)
{
	char	*token;
	t_token	*new;
	t_token	*ptr;

	token = ft_strdup((*node)->token);
	dmy_free((*node)->token);
	expand_token(envp, tokcod, &token);
	new = lex_it(token, 1, (*node)->next);
	if (!new)
		return ;
	if (pev)
		pev->next = new;
	ptr = new;
	ptr->token = token;
	while (ptr != (*node)->next)
	{
		dmy_free(*tokcod);
		*tokcod = create_tokcod(ptr->token);
		if (remove_quotes(tokcod, &(ptr->token)))
			yikes("invalid input for remove quotes", 0);
		ptr = ptr->next;
	}
	dmy_free(*node);
	*node = new;
}
