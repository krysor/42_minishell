/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:04:26 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/02 12:24:03 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_i_option_n(char **args);
static char	arg_to_option(char *arg);

int	ft_echo(char **args, char ***envp)
{
	int	i;
	int	option_n;

	(void)envp;
	if (!args || !*args)
		return (1);
	option_n = FALSE;
	i = get_i_option_n(args);
	if (i > 0)
		option_n = TRUE;
	if (i < 0)
		i = -i;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (option_n == FALSE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

//Returns a positive integer if a valid '-e' option has been found.
//Otherwise it returns a negative integer.
//
//The absolute value of the returned integer is equal to the first
//element of the array 'args' that should get printed: args[abs(int)].
static int	get_i_option_n(char **args)
{
	int	option_n;
	int	i;
	int	option;

	option_n = FALSE;
	i = 1;
	while (args[i])
	{
		option = arg_to_option(args[i]);
		if (option == '\0')
			break ;
		else if (option == 'n')
		{
			option_n = TRUE;
			i++;
		}
		else if (option == 'e')
			i++;
	}
	if (option_n == TRUE)
		return (i);
	return (-i);
}

static char	arg_to_option(char *arg)
{
	char	option;
	int		i;

	if (arg == NULL || arg[0] != '-')
		return ('\0');
	option = '\0';
	i = 1;
	while (arg[i] == 'e' || arg[i] == 'E')
	{
		option = 'e';
		i++;
	}
	if (arg[i] == 'n')
		option = 'n';
	while (arg[i] == 'e' || arg[i] == 'E' || arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return ('\0');
	return (option);
}
