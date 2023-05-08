/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:26:26 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/08 09:34:21 by yaretel-         ###   ########.fr       */
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
		dmy_free(buffer);
		buffer = dmy_malloc(sizeof(char) * (BUFFER_SIZE_PWD + i));
		if (!buffer)
			return (NULL);
		cwd = getcwd(buffer, BUFFER_SIZE_PWD);
		i++;
	}
	return (cwd);
}

int	var_in_envp(char *var, char **envp)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i]
		&& (ft_strncmp(envp[i], var, len)
			|| len != ft_strlen(envp[i])))
		i++;
	if (envp[i] == NULL)
		return (FALSE);
	return (TRUE);
}

int	ft_env(char **args, char ***ep)
{
	int		i;
	char	**envp;

	(void)args;
	envp = *ep;
	if (!envp)
		return (0);
	if (get_i_var("PATH", envp) == -1)
		return (1);
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}

int	ft_exit(char **args, char ***envp)
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
