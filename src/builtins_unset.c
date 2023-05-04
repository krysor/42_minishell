/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:56:15 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/03 16:25:53 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_i_var(char *var, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i] && (ft_strncmp(envp[i], var, len) || envp[i][len] != '='))
		i++;
	if (envp[i])
		return (i);
	return (-1);
}

int	ft_unset(char **args, char ***envp)
{
	int	i;

	if (!args || !args[0])
		return (1);
	if (!args[1] || !envp || !envp[0])
		return (0);
	i = 1;
	while (args[i])
	{
		ft_unset_var(args[i], envp);
		i++;
	}
	return (0);
}

void	ft_unset_var(char *arg, char ***envp_pnt)
{
	char	**envp;
	int		i;

	envp = *envp_pnt;
	i = get_i_var(arg, envp);
	if (i == -1)
		return ;
	free(envp[i]);
	while (envp[i + 1])
	{	
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}
