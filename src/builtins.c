/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:26:26 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/12 17:36:54 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getcwd(void);

int	ft_cd(char **args)//working, have to update PWD and OLDPWD
{
	char	*cwd_next;
	
	if (!args || !*args)
		return (1);
	cwd_next = args[1];
	if (!cwd_next || (ft_strlen(args[1]) == 1 && *args[1] == '~'))
		cwd_next = getenv("HOME");
	else if (ft_strlen(args[1]) == 1 && *args[1] == '-')
		cwd_next = getenv("OLDPWD");
	if (chdir(cwd_next))
		return (1);//return error code
	if (ft_strlen(args[1]) == 1 && *args[1] == '-' && ft_pwd(NULL))
		return (1);
	//HERE UPDATE OLDPWD AND PWD
	return (0);
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

char	*ft_getcwd(void)//merge back with pwd?
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

int ft_exit(char **args)
{
	int	i;

	if (!args)
		return (1);
	if (args[0] && !args[1])
		exit(0);
	i = 0;
	if (args[1][i] == '+' || args[1][i] == '-')
		i++;
	while (ft_isdigit(args[1][i]))
		i++;
	if (args[1][i] != '\0')
		exit(1);//return some more specific error code???
	exit(ft_atoi(args[1]));
}