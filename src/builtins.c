/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:26:26 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/11 15:55:10 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getcwd(void);

static int	get_i_option_e(char **args);

int	ft_echo(char **args)//improve it + not working atm
{
	int	i;
	int	option_e;
	
	if (!args || !*args)
		return (1);
	i = get_i_option_e(args);
	option_e = 0;
	if (i < 0)
		option_e = 1;
	if (i < 0)
		i *= -1;
	i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!option_e)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

static int	get_i_option_e(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i] && args[i][j] == '-'
		&& (args[i][j] == 'e' || args[i][j] == 'E' || args[i][j] == 'n'))//this loop should stop once first encounter
	{
		j = 1;
		while (args[i][j] == 'e' || args[i][j] == 'E')
			j++;
		if (args[i][j] == 'n')
			return (i);
		i++;
		j = 0;
	}
	return (-i);
}

int	ft_cd(char **args)//this has to change the oldpwd and pwd values in env
{
	char	*path;
	char	*pwd;
	int		result;
	
	if (args && args[0] && args[1] && args[2])
		return (1);
	path = args[1];

	//if (ft_strlen(path) == 1 && *path == '.')

	if (!chdir(path))
		return (0);
	pwd = ft_getcwd();
	if (!pwd)
		return (1);
	path = ft_strjoin(pwd, path);
	free(pwd);
	result = chdir(path);
	free(path);
	if (!result)
		return (0);
	return (1);
}

int	ft_pwd(char **args)
{
	char	*pwd;

	(void)args;
	pwd = ft_getcwd();
	if (!pwd)
		return (1);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(pwd);
	return (0);
}

char	*ft_getcwd(void)
{
	char	*cwd;
	char	*buffer;
	int		i;

	cwd = NULL;
	buffer = NULL;
	i = 0;
	while (!cwd)
	{
		free(buffer);
		buffer = malloc(sizeof(char) * (BUFFER_SIZE_PWD + i));
		if (!buffer)
			return (NULL);
		cwd = getcwd(buffer, BUFFER_SIZE_PWD);
		i++;
	}
	return (cwd);
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