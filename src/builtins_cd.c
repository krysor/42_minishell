/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:00:35 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/09 16:23:19 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check(char *path_abs, char *cwd);
static int	path_is_dir(char *path);
static int	env_pwd_update(char *pwd_old, char ***envp);
static int	var_update(char *var_name, char *var_val, char ***envp);

int	ft_cd(char **args, char ***envp)
{
	char	*pwd_old;
	char	*cwd_next;

	pwd_old = ft_getcwd();
	if (pwd_old == NULL)
		return (1);
	cwd_next = args[1];
	if (cwd_next == NULL || (ft_strlen(args[1]) == 1 && *args[1] == '~'))
		cwd_next = ft_getenv(*envp, "HOME");
	else if (ft_strlen(args[1]) == 1 && *args[1] == '-')
		cwd_next = ft_getenv(*envp, "OLDPWD");
	if (check(cwd_next, pwd_old) || chdir(cwd_next)
		|| (ft_strlen(args[1]) == 1 && *args[1] == '-' && ft_pwd(NULL, NULL)))
	{
		dmy_free(pwd_old);
		return (2);
	}
	if (env_pwd_update(pwd_old, envp))
	{
		dmy_free(pwd_old);
		return (3);
	}
	dmy_free(pwd_old);
	return (0);
}

static int	check(char *path, char *cwd)
{
	char	*path_abs;
	char	*s;

	if (path_is_dir(path))
		return (0);
	s = ft_strjoin(cwd, "/");
	if (s == NULL)
		return (1);
	path_abs = ft_strjoin(s, path);
	dmy_free(s);
	if (path_abs == NULL)
		return (2);
	if (path_is_dir(path_abs))
	{
		dmy_free(path_abs);
		return (0);
	}
	dmy_free(path_abs);
	return (3);
}

static int	path_is_dir(char *path)
{
	int	result;
	DIR	*directory;

	result = FALSE;
	directory = opendir(path);
	if (directory)
	{
		result = TRUE;
		closedir(directory);
	}
	return (result);
}

static int	env_pwd_update(char *pwd_old, char ***envp)
{
	static int	not_first_cd_after_pwd_unset = FALSE;
	char		*pwd_new;
	char		*pwd_old_right;

	pwd_old_right = pwd_old;
	if (get_i_var("PWD", *envp) == -1
		&& ft_strlen(ft_getenv(*envp, "OLDPWD")) != 0
		&& not_first_cd_after_pwd_unset == FALSE)
	{
		pwd_old_right = "";
		not_first_cd_after_pwd_unset = TRUE;
	}
	if (var_update("OLDPWD", pwd_old_right, envp))
		return (1);
	pwd_new = ft_getcwd();
	if (!pwd_new)
		return (1);
	if (get_i_var("PWD", *envp) != -1 && var_update("PWD", pwd_new, envp))
		return (1);
	dmy_free(pwd_new);
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
		dmy_free(var_equal);
		dmy_free(var_equal_val);
		return (1);
	}
	dmy_free(var_equal);
	ft_export_var(&var_equal_val, envp);
	dmy_free(var_equal_val);
	return (0);
}
