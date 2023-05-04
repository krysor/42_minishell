/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:00:35 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/03 17:28:03 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	env_pwd_update(char *pwd_old, char ***envp);
static int	var_update(char *var_name, char *var_val, char ***envp);

/*
TO DO:
1. error codes
*/
int	ft_cd(char **args, char ***envp)
{
	char	*pwd_old;
	char	*cwd_next;

	if (!args || !*args)
		return (1);
	pwd_old = ft_getcwd();
	if (!pwd_old)
		return (1);
	cwd_next = args[1];
	if (!cwd_next || (ft_strlen(args[1]) == 1 && *args[1] == '~'))
		cwd_next = ft_getenv(*envp, "HOME");
	else if (ft_strlen(args[1]) == 1 && *args[1] == '-')
		cwd_next = ft_getenv(*envp, "OLDPWD");
	if (chdir(cwd_next) || (ft_strlen(args[1]) == 1
			&& *args[1] == '-' && ft_pwd(NULL, NULL)))
	{
		free(pwd_old);
		return (1);
	}
	if (env_pwd_update(pwd_old, envp))
		return (1);
	free(pwd_old);
	return (0);
}
//return error codes

static int	env_pwd_update(char *pwd_old, char ***envp)
{
	char	*pwd_new;
	char	*pwd_old_right;

	pwd_old_right = pwd_old;
	pwd_old_right = ft_getenv(*envp, "PWD");
	if (get_i_var("PWD", *envp) == -1
		&& ft_strlen(ft_getenv(*envp, "OLDPWD")) != 0)
		pwd_old_right = "";
	if (var_update("OLDPWD", pwd_old_right, envp))
		return (1);
	pwd_new = ft_getcwd();
	if (!pwd_new)
		return (1);
	if (get_i_var("PWD", *envp) != -1 && var_update("PWD", pwd_new, envp))
		return (1);
	free(pwd_new);
	return (0);
}

static int	var_update(char *var_name, char *var_val, char ***envp)
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
	ft_export_var(&var_equal_val, envp);
	free(var_equal_val);
	return (0);
}
