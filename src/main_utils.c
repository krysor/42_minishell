/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:03:35 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/20 18:34:22 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_updated_shlvl(char **envp[]);

int	init_shell(char **envp[])
{
	char	*shlvl;

	g_exit_code = 0;
	ft_putstr_fd(MSG_HELLO, STDOUT_FILENO);
	shlvl = get_updated_shlvl(envp);
	if (shlvl == NULL || ft_export_var(&shlvl, envp))
	{
		dmy_free(shlvl);
		free_arr(*envp);
		return (1);
	}
	dmy_free(shlvl);
	return (0);
}

static char	*get_updated_shlvl(char **envp[])
{
	char	*s;
	char	*shlvl;
	int		lvl;

	s = ft_getenv(*envp, "SHLVL");
	if (s == NULL)
		shlvl = ft_strdup("SHLVL=1");
	else
	{
		lvl = ft_atoi(s);
		if (lvl <= 0)
			shlvl = ft_strdup("SHLVL=1");
		else
		{
			lvl++;
			if (lvl - 1 > lvl)
				return (NULL);
			s = ft_itoa(lvl);
			shlvl = ft_strjoin("SHLVL=", s);
			dmy_free(s);
		}
	}
	return (shlvl);
}
