/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_toknode_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:00:44 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/25 14:44:07 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

ssize_t	value_len_diff(char *dlr)
{
	char			*var;
	size_t			var_len;
	size_t			value_len;

	if (!dlr)
		yikes("Error during expansion: value_len_diff() input protection\n", 0);
	var_len = 1;
	if (!dlr[var_len] || is_mchar(&dlr[var_len]) || is_quote(&dlr[var_len]))
		return (0);
	while (dlr[var_len] && !is_mchar(&dlr[var_len]) && !is_quote(&dlr[var_len]))
		var_len++;
	var = malloc(sizeof(*var) * ((var_len + 1) - 1));
	if (!var)
		yikes("malloc failed\n", 0);
	ft_memcpy(var, dlr + 1, var_len - 1);
	var[var_len] = '\0';
	value_len = ft_strlen(getenv(var));
	free(var);
	return (value_len - var_len);
}

void	expand_var(char *dest, char *dollar, unsigned int *i, unsigned int *j)
{
	size_t			dlen;
	char			*allowed;
	char			temp;

	dollar++;
	if (!getenv(dollar))
	{
		(*i)++;
		return ;
	}
	allowed = "0123456789_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	dlen = seqstrlen(dollar, allowed);
	temp = dollar[dlen + 1];
	dollar[dlen + 1] = '\0';
	*j += ft_strlcpy(dest, getenv(dollar), SIZE_MAX) + 1;
	dollar[dlen] = temp;
	*i += dlen;
}
