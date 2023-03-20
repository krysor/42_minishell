/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:36:53 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/20 09:44:47 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

ssize_t	value_len_diff(char *dollar)
{
	char			*var;
	size_t			var_len;
	size_t			value_len;

	if (!dollar)
		yikes("Error during expansion: value_len_diff() input protection\n", 0);
	var_len = 1;
	if (!dollar[var_len] || is_mchar(&dollar[var_len]) || is_quote(&dollar[var_len]))
		return (0);
	while (dollar[var_len] && !is_mchar(&dollar[var_len]) && !is_quote(&dollar[var_len]))
		var_len++;
	var = malloc(sizeof(*var) * ((var_len + 1) - 1));
	if (!var)
		yikes("malloc failed\n", 0);
	ft_memcpy(var, dollar + 1, var_len - 1);
	var[var_len] = '\0';
	value_len = ft_strlen(getenv(var));
	free(var);
	return (value_len - var_len);
}

char	*trim(char **token, char *del)
{
	unsigned int	i;
	char			*new;
	size_t			newlen;

	i = 0;
	while (is_in_set((*token)[i], del))
		i++;
	newlen = strdlen(*token + i, del); 
	new = malloc(sizeof(*new) * (newlen + 1));
	if (!new)
		yikes("malloc fail\n", 0);
	ft_strlcpy(new, *token + i, newlen + 1);
	free(*token);
	*token = new;
	return(*token);
}

void	expand_var(char *dest, char *dollar, unsigned int *i, unsigned int *j)
{
	size_t			dlen;
	char			*allowed;
	char			temp;

	if (*dollar == '$')
		dollar++;
	allowed = "0123456789_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	dlen = seqstrlen(dollar, allowed);
	temp = dollar[dlen];
	dollar[dlen] = '\0';
	*j += ft_strlcpy(dest, getenv(dollar), SIZE_MAX);
	dollar[dlen] = temp;
	*i += dlen;
}

char	*expand_token(char *token, size_t newlen)
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
		if (token[i] == '$')
			expand_var(new + j, token + i, &i, &j);
		else
			new[j++] = token[i++];
	}
	return (new);
}

void	expand_node(t_token *node, t_token *prev)
{
	unsigned int	i;
	size_t			newlen;
	char			*expanded;

	if (!node)
		yikes("unexpected NULL pointer\n", 0);
	newlen = ft_strlen(node->token);
	if (node->token[0] == '\'' && node->token[newlen] == '\'')
	{
		node->interprete = FALSE;
		trim(&node->token, "\'");
		return ;
	}
	i = 0;
	while ((node->token)[i])
	{
		if ((node->token)[i] == '$')
			newlen += value_len_diff(node->token + i);
		i++;
	}
	expanded = expand_token(node->token, newlen);
	free(node->token);
	if (expanded[0] == '\"' && expanded[newlen] == '\"')
	{
		node->interprete = FALSE;
		node->token = trim(&expanded, "\"");
	}
	else 
	{
		prev->next = lex_it(expanded, FALSE, node->next);
		free(node);
	}
	free(expanded);
}
