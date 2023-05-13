/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:26:26 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/12 18:34:16 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//error check done
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
	dmy_free(pwd);
	return (0);
}

int	ft_env(char **args, char ***ep)
{
	int		i;
	char	**envp;

	if (ep == NULL || *ep == NULL)
		return (1);
	envp = *ep;
	if (get_i_var("PATH", envp) == -1)
	{
		ft_putstr_fd("env: No such file or directory\n", STDOUT_FILENO);
		return (127);
	}
	if (args[1] != NULL)
	{
		ft_putstr_fd(args[1], STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
		return (127);
	}
	i = -1;
	while (envp[++i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

/*
//printf("LONG_MIN casted to int divided by 256: %d\n", (int)(LONG_MAX % 256));
int	ft_exit(char **args, char ***envp)
{
	int	i;

	(void)envp;
	if (!args)
		return (1);
	if (args[0] && args[1] == NULL)
		exit(0);
	i = 0;

	if (args[1][i] == '+' || args[1][i] == '-')
		i++;
	while (ft_isdigit(args[1][i]))
		i++;

	if (args[1][i] != '\0')
		exit(1);

	exit(ft_atoi(args[1]));
}*/

int	ft_export(char **args, char ***envp)
{
	int	i;

	if (!args || !*args || !args[1] || !envp || !*envp)
		return (1);
	i = 1;
	while (args[i])
	{
		if (ft_export_var(&args[i], envp))
			return (1);
		i++;
	}
	return (0);
}
