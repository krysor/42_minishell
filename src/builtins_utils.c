/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:55:57 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/08 10:58:57 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_i_var(char *var, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i] && (ft_strncmp(envp[i], var, len) || envp[i][len] != '='))
		i++;
	if (envp[i])
		return (i);
	return (-1);
}

char	*ft_getcwd(void)
{
	char	*cwd;
	char	*buffer;
	int		i;

	cwd = NULL;
	buffer = NULL;
	i = 0;
	while (cwd == NULL && BUFFER_SIZE_PWD + i < BUFFER_SIZE_PWD_MAX)
	{
		dmy_free(buffer);
		buffer = dmy_malloc(sizeof(char) * (BUFFER_SIZE_PWD + i));
		if (!buffer)
			return (NULL);
		cwd = getcwd(buffer, BUFFER_SIZE_PWD);
		i++;
	}
	if (cwd == NULL && BUFFER_SIZE_PWD + i == BUFFER_SIZE_PWD_MAX)
		return (ft_strdup(""));
	return (cwd);
}

long int	ft_atolong(const char *nptr)
{
	long int	nb;
	int			sign;
	char		*str;

	nb = 0;
	sign = 1;
	str = (char *)nptr;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (ft_strncmp(str + 1, STR_LONG_MIN, 19) == 0)
		return (LONG_MIN);
	while (ft_isdigit(*str))
		nb = nb * 10 + *str++ - '0';
	return (nb * sign);
}

int	ft_isspace(char chr)
{
	if (chr == ' ' || chr == '\f' || chr == '\n'
		|| chr == '\r' || chr == '\t' || chr == '\v')
		return (1);
	return (0);
}

int	ft_nbdigit(char *s)
{
	int	nb;

	nb = 0;
	while (*s && ft_isdigit(*s))
	{
		nb++;
		s++;
	}	
	return (nb);
}
