/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:26:26 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/10 11:20:06 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	new_line;
	
	if (!args)
		return (1);
	i = 1;
	new_line = 1;
	while (args[i] && *args[i] == '-')
	{
		if (ft_memchr(args[i], 'n', ft_strlen(args[i])))
			new_line = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	ft_cd(char **args)//this has to change the oldpwd and pwd values in env
{
	char	*path;
	DIR		*dir;
	
	if (args && args[0] && args[1] && args[2])
		return (1);
	path = args[1];
	dir = opendir(path);
	if (dir)
	{
		chdir(path);
		closedir(dir);
		return (0);
	}
	// path = ft_strjoin(ft_pwd(NULL), path);//make char *get_pwd f from ft_pwd and use t here
	if (!path)
		return (1);
	dir = opendir(path);
	if (dir)
	{
		chdir(path);
		closedir(dir);
		return (0);
	}
	return (1);
}

int	ft_pwd(char **args)
{
	char	*pwd;
	char	*buffer;
	int		i;

	(void)args;
	pwd = NULL;
	buffer = NULL;
	i = 0;
	while (!pwd)
	{
		free(buffer);
		buffer = malloc(sizeof(char) * (BUFFER_SIZE_PWD + i));
		if (!buffer)
			return (1);
		pwd = getcwd(buffer, BUFFER_SIZE_PWD);
		i++;
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(buffer);
	return (0);
}

int ft_export(char **args)
{
	(void)args;
	return (0);
}

int ft_unset(char **args)
{
	(void)args;
	return (0);
}

int ft_env(char **args)//this has to update the pwd value on each call
{
	(void)args;
	return (0);
}

int ft_exit(char **args)//not sure whether this one should work with fork
{
	int	exit_code;

	if (!args)
		return (1);
	exit_code = 0;
	if (args[0] && args[1] && *args[1])
		exit_code = ft_atoi(args[1]);
	exit(exit_code);//problem: cmd and args are not yet freed at this moment
	return (0);
}