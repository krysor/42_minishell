/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:26:26 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/19 13:50:20 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getcwd(void);
int		env_pwd_update(char *pwd_old, char ***envp);
int		var_create(char *var_name, char *var_val, char ***envp);

/*
TO DO:
1. error codes
*/
int	ft_cd(char **args, char ***envp)
{
	char	*wd;
	char	*cwd_next;

	if (!args || !*args)
		return (1);
	wd = ft_getcwd();
	if (!wd)
		return (1);
	cwd_next = args[1];
	if (!cwd_next || (ft_strlen(args[1]) == 1 && *args[1] == '~'))
		cwd_next = ft_getenv(*envp, "HOME");
	else if (ft_strlen(args[1]) == 1 && *args[1] == '-')
		cwd_next = ft_getenv(*envp, "OLDPWD");
	if (chdir(cwd_next) || (ft_strlen(args[1]) == 1
		&& *args[1] == '-' && ft_pwd(NULL, NULL)))
	{
		free(wd);
		return (1);//return error code
	}
	if (env_pwd_update(wd, envp))
		return (1);
	free(wd);
	return (0);
}

int	env_pwd_update(char *pwd_old, char ***envp)
{
	char	*pwd_new;
	
	if (var_create("OLDPWD", pwd_old, envp))
		return (1);
	pwd_new = ft_getcwd();
	if (!pwd_new)
		return (1);
	if (var_create("PWD", pwd_new, envp))
		return (1);
	return (0);
}

int	var_create(char *var_name, char *var_val, char ***envp)
{
	char	*var_equal;
	char	*var_equal_val;
	
	ft_unset_var(var_name, envp);
	var_equal = ft_strjoin(var_name, "=");
	var_equal_val = ft_strjoin(var_equal, var_val);
	if (!var_equal || !var_equal_val)
	{
		free(var_equal);
		free(var_equal_val);
		return (1);
	}
	free(var_equal);
	ft_export_var(var_equal_val, envp);
	free(var_equal_val);
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

int	var_in_envp(char *var, char **envp)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(envp[i]);
	while (envp[i] && (ft_strncmp(envp[i], var, len) || len != ft_strlen(envp[i])))
		i++;
	if (envp[i] == NULL)
		return (0);
	return (1);
}

int ft_env(char **args, char ***ep)

{
	int		i;
	char	**envp;
	
	(void)args;
	envp = *ep;
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
		exit(1);//return some more specific error code???
	exit(ft_atoi(args[1]));
}
