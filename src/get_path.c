/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:36:10 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/21 12:10:12 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_path(char **arr, char *s);
static char	**get_all_paths(char **envp);

/*
char	*get_path(char *cmd, char **envp)
{
	char	*s;
	char	**arr;
	char	*path;

	s = ft_strjoin("/", cmd);
	if (!s)
		return (NULL);
	arr = get_all_paths(envp);
	if (!arr)
	{
		dmy_free(s);
		return (NULL);
	}
	path = find_path(arr, s);
	dmy_free(s);
	free_arr(arr);
	if (!path)
		return (ft_strdup(cmd));
	return (path);
}*/

char	*get_path(char *cmd, char **envp)
{
	char	*s;
	char	**arr;
	char	*path;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	s = ft_strjoin("/", cmd);
	if (!s)
		return (NULL);
	if (ft_getenv(envp, "PATH") == NULL)
		return (ft_strdup(cmd));
	arr = get_all_paths(envp);
	if (!arr)
	{
		dmy_free(s);
		return (NULL);
	}
	path = find_path(arr, s);
	dmy_free(s);
	free_arr(arr);
	if (!path)
		return (ft_strdup(cmd));
	return (path);
}

static char	**get_all_paths(char **envp)
{
	char	*env_path;
	char	**paths;

	env_path = ft_getenv(envp, "PATH");
	if (env_path == NULL)
		return (NULL);
	paths = ft_split(env_path + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*find_path(char **arr, char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (arr[i])
	{
		temp = ft_strjoin(arr[i], s);
		if (!temp)
			return (NULL);
		dmy_free(arr[i]);
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
		return (ft_strdup(arr[i]));
	return (NULL);
}
