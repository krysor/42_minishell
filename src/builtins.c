/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:26:26 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/17 09:57:00 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getcwd(void);
int		ft_export_var(char **arg, char ***envp_pnt);
int		ft_unset_var(char **arg, char ***envp_pnt);

/*
TO DO:
1. error codes
2. update OLDPWD and PWD in env
*/
int	ft_cd(char **args)
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
	if (ft_strlen(args[1]) == 1 && *args[1] == '-' && ft_pwd(NULL, NULL))
		return (1);
	return (0);
}

int	ft_pwd(char **args, char ***envp)
{
	char	*pwd;

	(void)args;
	(void)envp;
	pwd = ft_getcwd();
	if (!pwd)
		return (1);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(pwd);
	return (0);
}

/*
Merge back with pwd*/
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

int ft_export(char **args, char ***envp)
{
	(void)envp;
	(void)args;
	return (0);
}

{
	int	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}

int ft_exit(char **args, char ***envp)
{
	int	i;

	(void)envp;
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
		exit(1);
	exit(ft_atoi(args[1]));
}
