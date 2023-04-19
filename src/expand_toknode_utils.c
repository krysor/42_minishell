/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_toknode_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:00:44 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/19 15:39:47 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

ssize_t	value_len_diff(char *dlr, char **envp)
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
	var = malloc(sizeof(char) * ((var_len + 1) - 1));
	if (!var)
		yikes("malloc failed\n", 0);
	ft_memcpy(var, dlr + 1, var_len - 1);
	var[var_len - 1] = '\0';
	value_len = ft_strlen(ft_getenv(envp, var));
	free(var);
	return (value_len - var_len);
}

void	expand_var(char *dest, char *dollar, unsigned int *i, unsigned int *j, char **envp)
{
	size_t			dlen;
	char			*allowed;
	char			temp;

	dollar++;
	if (!ft_getenv(envp, dollar))
	{
		(*i)++;
		return ;
	}
	allowed = "0123456789_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	printf("segf1?\n");
	dlen = seqstrlen(dollar, allowed);
	//temp = dollar[dlen];
	temp = dollar[dlen + 1];
	//printf("segf2?\n");
	dollar[dlen + 1] = '\0'; 
	*j += ft_strlcpy(dest, ft_getenv(envp, dollar), SIZE_MAX) + 1;
	dollar[dlen] = temp;
	*i += dlen;
}

char	*ft_getenv(char *ep[], char *name)
{
	int	i;

	if (!ep || !ep[0] || !name)
		return (NULL);
	i = get_i_var(name, ep);
	if (i == -1)
		return (NULL);
	return (1 + ft_memchr(ep[i], '=', ft_strlen(ep[i])));
}

/*
char	*ft_getenv(char *ep[], const char *name)
{
	unsigned int	i;
	char			*d;

	if (!ep || !ep[0] || !name)
		return (NULL);
	i = 0;
	while (ep[i] && (ft_strncmp(ep[i], name, strdlen(ep[i], "=")) || ft_strncmp(ep[i], name, ft_strlen(name))))//find member that has same value as second parameter
		i++;
	if (!ep[i])
		return (NULL);
	d = ft_strrchr(ep[i], '=');//look for the last '=' in the string
	if (d && *d)
		return (d + 1);//return the first character of the value part of the string
	return (NULL);
}*/
