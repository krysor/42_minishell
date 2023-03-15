/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:26:04 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/13 16:50:13 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	put_prompt(char *envp[]);

//TO_SOLVE: prompt gets deleted when deleting whole line after writing smth
int main(int argc, char *argv[], char *envp[])
{
	char	*str;
	
	(void)argc;
	(void)argv;
	str = malloc(1);
	while (ft_strlen(CMD_EXIT) != ft_strlen(str) ||
			ft_strncmp(CMD_EXIT, str, ft_strlen(CMD_EXIT)))
	{
		put_prompt(envp);
		free(str);
		str = readline(NULL);
		//DO THE SHELL THING WITH THE STR HERE
	}
	ft_putstr_fd(CMD_EXIT, 1);
	free(str);
	return (0);
}

static void	put_prompt(char *envp[])
{
	char	*env;

	env = ft_get_env_val(envp, "USER");
	if (env)
		ft_putstr_fd(env, 1);
	ft_putstr_fd("$ ", 1);
}
