/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:56:03 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/08 10:42:30 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_plus(char **arg_pnt, int i_equal, char **envp);
static int	var_name_illegal(char *arg);
static int	envp_cpy(char ***envp_old_pnt, char *arg);
static int	ft_unset_arg(char *arg, char ***envp_pnt);

int	ft_export_var(char **arg_pnt, char ***envp_pnt)
{
	char	*arg;
	char	*arg_equal;
	int		i_equal;

	if (arg_pnt == NULL)
		return (1);
	arg = *arg_pnt;
	arg_equal = ft_memchr(arg, '=', ft_strlen(arg));
	if (arg_equal == NULL)
		return (2);
	if (arg[0] == '=' || (arg[0] == '+' && arg[1] == '='))
		return (3);
	i_equal = arg_equal - arg;
	if (arg[i_equal - 1] == '+' && handle_plus(arg_pnt, i_equal - 1, *envp_pnt))
		return (4);
	if (var_name_illegal(arg))
		return (5);
	if (ft_unset_arg(*arg_pnt, envp_pnt))
		return (6);
	if (envp_cpy(envp_pnt, *arg_pnt))
		return (7);
	return (0);
}

static int	handle_plus(char **arg_pnt, int i_plus, char **envp)
{
	char	*arg;
	int		i_var_old;
	char	*arg_temp;

	if (arg_pnt == NULL)
		return (1);
	arg = *arg_pnt;
	arg[i_plus] = '\0';
	i_var_old = get_i_var(arg, envp);
	arg[i_plus] = '+';
	if (i_var_old == -1)
		ft_memmove(arg + i_plus, arg + i_plus + 1,
			ft_strlen(arg) - i_plus);
	else
	{
		arg_temp = ft_strjoin(envp[i_var_old], arg + i_plus + 2);
		if (!arg_temp)
			return (1);
		dmy_free(arg);
		*arg_pnt = arg_temp;
	}
	return (0);
}

static int	var_name_illegal(char *arg)
{
	int	i;

	i = (char *)ft_memchr(arg, '=', ft_strlen(arg)) - arg;
	i -= 1;
	while (i >= 0)
	{
		if (ft_isalnum(arg[i]) || arg[i] == '_')
			i--;
		else
			return (1);
	}
	return (0);
}

static int	envp_cpy(char ***envp_old_pnt, char *arg)
{
	int		len_envp_old;
	char	**envp_new;
	int		i;

	len_envp_old = 0;
	while ((*envp_old_pnt)[len_envp_old])
		len_envp_old++;
	envp_new = dmy_malloc(sizeof(char *) * (len_envp_old + 2));
	if (envp_new == NULL)
		return (1);
	i = -1;
	while ((*envp_old_pnt)[++i])
		envp_new[i] = (*envp_old_pnt)[i];
	envp_new[i] = ft_strdup(arg);
	if (envp_new[i] == NULL)
	{
		dmy_free(envp_new);
		return (1);
	}
	envp_new[i + 1] = NULL;
	dmy_free(*envp_old_pnt);
	*envp_old_pnt = envp_new;
	return (0);
}

static int	ft_unset_arg(char *arg, char ***envp_pnt)
{
	char	*var;
	int		i;

	i = 0;
	var = ft_strdup(arg);
	if (var == NULL)
		return (1);
	while (var[i] != '=')
		i++;
	var[i] = '\0';
	ft_unset_var(var, envp_pnt);
	dmy_free(var);
	return (0);
}
