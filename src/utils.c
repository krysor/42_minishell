/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:05 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/13 16:44:49 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	yikes(char *msg, unsigned int ac, ...)
{
	va_list			list;
	unsigned int	i;

	i = 0;
	write(2, msg, ft_strlen(msg));
	va_start(list, ac);
	while (i < ac)
	{
		free(va_arg(list, void *));
		i++;
	}
	va_end(list);
}	

// Checks if input is metacharacter (see bash manual)
char	*is_mchar(char *c)
{
	if (*c == '<' || *c == '>' || *c == '|')
		return (c);
	else if (*c == ' ' || *c == '\t' || *c == '\n')
		return (c);
	else
		return (NULL);
}

// Checks if input is a quote
char	*is_quote(char *c)
{
	if (*c == '\'' || *c == '\"')
		return (c);
	else
		return (NULL);
}

char	*ft_memcpy(char *src, char *dst, size_t len)
{
	size_t	i;

	if (!src || !dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{	
	while (n && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}

//retruns the value of the environment variable env
char	*ft_get_env_val(char *envp[], char *env)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], env, ft_strlen(env)))
			break ;
		i++;
	}
	return (ft_memchr(envp[i], '=', ft_strlen(envp[i])) + 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}
