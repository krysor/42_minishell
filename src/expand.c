/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:40:09 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/12 12:31:19 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

ssize_t	value_len_diff(char *dollar)
{
	char			*var;
	char			*value;
	size_t			var_len;
	size_t			value_len;

	if (!dollar)
	{
		write(2, "Error during expansion: varvallen() input protection\n", 53);
	}
	var_len = 1;
	if (!dollar[var_len] || is_mchar(dollar[var_len]) || is_quote(dollar[var_len]))
		return (0);
	while (dollar[var_len] && !is_mchar(dollar[var_len]) && !is_quote(dollar[var_len]))
		var_len++;
	var = malloc(sizeof(*var) * ((var_len + 1) - 1));
	ft_memcpy(var, dollar + 1, var_len - 1);
	var[var_len] = '\0';
	value_len = ft_strlen(getenv(var));
	free(var);
	return (value_len - var_len);
}

size_t	newlen(char *pt, char *wc)
{
	size_t			len;
	unsigned int	i;

	if (!pt || !wc)
	{
		write(2, "Error during expansion: prompt or wordcoding empty\n", 51);
	}
	len = ft_strlen(pt);
	i = 0;
	while (pt)
	{
		if (pt[i] == '$' && wc[i] != '\'')
			len += value_len_diff(&pt[i]);
		i++;
	}
	return (len);
}

size_t	expand_var(char *var, char *value)
{
	

char	*expand(char *pt, char *wc)
{
	char			*new;
	size_t			newlen;
	t_envvar		envvars;
	unsigned int	i;
	unsigned int	j;
	unsigned int	increment;

	if (!pt || !wc)
		write(2, "Error during expansion: prompt or wordcoding empty\n", 51);
	envvars = get_envvars(pt, wc, &newlen);
	new = malloc(sizeof(*new) * (newlen + 1));
	i = 0;
	j = 0;
	while (pt[i])
	{
		if (pt[i] != '$' || wc[i] != '\'')
		{
			new[j++] = pt[i];
			i++;
		}
		else
		{
			increment += write_nextvar(envvars);
			i += increment;
			j += increment;
		}
	}
	return (new)
}
