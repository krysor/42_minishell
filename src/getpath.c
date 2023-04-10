/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:36:10 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/08 16:01:37 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*findpath(char **arr, char *s);
static char	**getallpaths(void);

char	*getpath(char *cmd)
{
	char	*s;
	char	**arr;
	char	*path;

	s = ft_strjoin("/", cmd);
	if (!s)
		return (NULL);
	arr = getallpaths();
	if (!arr)
	{
		free(s);
		return (NULL);
	}
	path = findpath(arr, s);
	free(s);
	free_arr(arr);
	if (!path)
		return (ft_strdup(cmd));
	return (path);
}

static char	**getallpaths(void)
{
	char	*env_path;
	char	**paths;

	env_path = getenv("PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*findpath(char **arr, char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (arr[i])
	{
		temp = ft_strjoin(arr[i], s);
		if (!temp)
			return (NULL);
		free(arr[i]);
		arr[i++] = temp;
	}
	i = 0;
	while (arr[i])
	{
		if (!access(arr[i], X_OK))
			break ;
		i++;
	}
	if (arr[i])
		return(ft_strdup(arr[i]));
	return (NULL);
}
