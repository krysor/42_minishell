/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:26:26 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/17 17:26:15 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getcwd(void);
int		ft_export_var(char **arg, char ***envp_pnt);
int		ft_unset_var(char **arg, char ***envp_pnt);

int	ft_cd(char **args, char ***envp)//working, have to update PWD and OLDPWD
{
	char	*cwd_next;
	
	if (!args || !*args)
		return (1);
	cwd_next = args[1];
	if (!cwd_next || (ft_strlen(args[1]) == 1 && *args[1] == '~'))
		cwd_next = ft_getenv(*envp, "HOME");
	else if (ft_strlen(args[1]) == 1 && *args[1] == '-')
		cwd_next = ft_getenv(*envp, "OLDPWD");
	if (chdir(cwd_next))
		return (1);//return error code
	if (ft_strlen(args[1]) == 1 && *args[1] == '-' && ft_pwd(NULL, NULL))
		return (1);
	//HERE UPDATE OLDPWD AND PWD
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

int	ft_export_var(char **ag, char ***envp_pnt)//add to check if var already exists in env
{
	char	*sign_equal;
	char	**envp_new;
	int		envp_len;
	char	*arg;

	arg = *ag;
	sign_equal = ft_memchr(arg, '=', ft_strlen(arg));
	if (!sign_equal || sign_equal - arg == 0 || var_in_envp(arg, *envp_pnt))
		return (1);//check correct errno later, possibly make 2 apart cases
	envp_len = 0;
	while ((*envp_pnt)[envp_len])
		envp_len++;
	envp_new = malloc(sizeof(char *) * (envp_len + 2));
	if (!envp_new)
		return (1); //check correct errno later
	envp_len = -1;
	while ((*envp_pnt)[++envp_len])
		envp_new[envp_len] = (*envp_pnt)[envp_len];
	envp_new[envp_len] = ft_strdup(arg);
	if (!envp_new[envp_len])
	{
		free_arr(envp_new);
		return (1); //check correct erno later
	}
	envp_new[envp_len + 1] = NULL;
	free(*envp_pnt);
	*envp_pnt = envp_new;
	return (0);
}

/*
int	ft_export_var(char *arg, char ***envp_pnt)//add to check if var already exists in env
{
	char	*sign_equal;
	char	**envp_new;
	int		envp_len;

	if (var_in_envp(arg, *envp_pnt))
		return (1);//check correct errno later, possibly make 2 apart cases
	sign_equal = ft_memchr(arg, '=', ft_strlen(arg));
	if (!sign_equal || sign_equal - arg == 0)
		return (1); //check correct errno later, possibly make 2 apart cases
	envp_len = 0;
	while ((*envp_pnt)[envp_len])
		envp_len++;
	envp_new = malloc(sizeof(char *) * (envp_len + 2));
	if (!envp_new)
		return (1); //check correct errno later
	envp_len = -1;
	while ((*envp_pnt)[++envp_len])
		envp_new[envp_len] = (*envp_pnt)[envp_len];
	envp_new[envp_len] = ft_strdup(arg);
	if (!envp_new[envp_len])
	{
		free_arr(envp_new);
		return (1); //check correct erno later
	}
	envp_new[envp_len + 1] = NULL;
	free(*envp_pnt);
	*envp_pnt = envp_new;
	return (0);
}*/

int	ft_unset_var(char **ag, char ***envp_pnt)
{
	int		i;
	size_t	len;
	char	**envp;
	char	*arg;
	
	arg = *ag;
	i = 0;
	len = ft_strlen(arg);
	envp = *envp_pnt;
	while (envp[i] && (ft_strncmp(envp[i], arg, len)
		|| envp[i][len] != '='))
		i++;
	while (envp[i + 1])
	{	
		envp[i] = envp[i + 1];
		i++;
	}
	free(envp[i]);
	envp[i] = NULL;
	return (0);
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
