/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:04:26 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/28 17:25:40 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_i_option_e(char **args);
static int	is_option(char c);
static int	ft_abs(int i);

int	ft_echo(char **args, char ***envp)
{
	int	i;
	int	option_e;

	(void)envp;
	if (!args || !*args)
		return (1);
	option_e = 0;
	i = get_i_option_e(args);
	if (i > 0)
		option_e = 1;
	i = ft_abs(i);
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!option_e)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

//Returns a positive integer if a valid '-e' option has been found.
//Otherwise it returns a negative integer.
//
//The absolute value of the returned integer is equal to the first
//element of the array 'args' that should get printed: args[abs(int)].
static int	get_i_option_e(char **args)
{
	int	option_e;
	int	i;
	int	j;

	option_e = 0;
	i = 1;
	j = 1;
	while (args[i] && args[i][0] == '-' && is_option(args[i][1]))
	{
		while (args[i][j] == 'e' || args[i][j] == 'E')
			j++;
		if (args[i][j] == 'n')
			option_e = 1;
		while (is_option(args[i][j]))
			j++;
		if (args[i][j] == '\0' && option_e)
			return (i + 1);
		if (args[i][j] != '\0')
			return (-i);
		i++;
		j = 1;
	}
	return (-i);
}

static int	is_option(char c)
{
	if (c == 'e' || c == 'E' || c == 'n')
		return (1);
	return (0);
}

static int	ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}
