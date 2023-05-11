/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:19:00 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/11 12:53:22 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_gnl_nl(char *buffer);
static char	*ft_gnl_no_nl(char *buffer, int fd);

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			nb_read;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (!buffer || buffer[0] == '\0')
	{
		if (!buffer)
			buffer = dmy_malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read <= 0)
		{
			dmy_free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[nb_read] = '\0';
		return (get_next_line(fd));
	}
	if (ft_memchr(buffer, '\n', ft_strlen(buffer)))
		return (ft_gnl_nl(buffer));
	return (ft_gnl_no_nl(buffer, fd));
}

static char	*ft_gnl_nl(char *buffer)
{
	int		i;
	int		l;
	char	*s;

	i = (char *)ft_memchr(buffer, '\n', ft_strlen(buffer)) - buffer;
	buffer[i] = '\0';
	l = ft_strlen(buffer);
	s = dmy_malloc(sizeof(char) * (l + 2));
	if (!s)
	{
		dmy_free(buffer);
		return (NULL);
	}
	s = (char *)ft_memcpy(s, buffer, l);
	s[l] = '\n';
	s[l + 1] = '\0';
	if (ft_strlen(s) == BUFFER_SIZE
		|| !ft_strlen(buffer + i + 1))
		buffer[0] = '\0';
	else
		ft_memmove(buffer, buffer + l + 1, BUFFER_SIZE - l);
	return (s);
}

static char	*ft_gnl_no_nl(char *buffer, int fd)
{
	char	*s1;
	char	*s2;
	char	*s3;
	int		l;

	l = ft_strlen(buffer);
	s1 = dmy_malloc(sizeof(char) * (l + 1));
	if (!s1)
		dmy_free(buffer);
	if (!s1)
		return (NULL);
	s1 = (char *)ft_memcpy(s1, buffer, l + 1);
	buffer[0] = '\0';
	s2 = get_next_line(fd);
	if (!s2)
		return (s1);
	s3 = ft_strjoin(s1, s2);
	dmy_free(s1);
	dmy_free(s2);
	if (!s3)
		dmy_free(buffer);
	if (!s3)
		return (NULL);
	return (s3);
}