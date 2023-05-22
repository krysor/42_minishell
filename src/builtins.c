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
		ft_putstr_fd("env: No such file or directory\n", STDERR_FILENO);
		return (127);
	}
	if (args[1] != NULL)
	{
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
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

int	ft_export(char **args, char ***envp)
{
	int	i;

	if (args == NULL || args[0] == NULL
		|| envp == NULL || *envp == NULL)
		return (1);
	if (args[1] == NULL)
		return (ft_export_noargs(*envp));
	i = 1;
	while (args[i])
	{
		if (ft_export_var(&args[i], envp))
			return (1);
		i++;
	}
	return (0);
}
