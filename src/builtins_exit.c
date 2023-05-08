/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:31:57 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/08 11:31:47 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	arg_is_correct(char *arg);
static int	arg_is_long(char *arg, int i);

int	ft_exit(char **args, char ***envp)
{
	int	exit_code;

	(void)envp;
	exit_code = get_exit_code(args);
	if (exit_code == 256)
		return (1);
	exit(exit_code);
}

int	get_exit_code(char **args)
{
	int	exit_code;

	ft_putstr_fd(CMD_EXIT, 1);
	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		exit_code = 256;
	}
	else if (args[1] == NULL)
		exit_code = 0;
	else if (arg_is_correct(args[1]) == FALSE)
	{
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd(args[1], 1);
		ft_putstr_fd(": numeric argument required", 1);
		exit_code = 255;
	}
	else
		exit_code = ft_atolong(args[1]) % 256;
	//printf("exit_code: %d\n", exit_code);
	return (exit_code);
}

static int	arg_is_correct(char *arg)
{
	int	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i] != '\0')
		return (FALSE);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i] == '0')
		i++;
	if (arg[i] == '\0')
		i--;
	if (arg_is_long(arg, i) == FALSE)
		return (FALSE);
	return (TRUE);
}

static int	arg_is_long(char *arg, int i)
{
	int	nb_digits;

	nb_digits = ft_nbdigit(arg + 1);
	if (nb_digits > 19)
		return (FALSE);
	if (nb_digits == 19)
	{
		if ((ft_isdigit(arg[i]) || arg[i] == '+')
			&& ft_strncmp(STR_LONG_MAX, arg + i, 19))
			return (FALSE);
		if ((ft_isdigit(arg[i]) || arg[i] == '-')
			&& ft_strncmp(STR_LONG_MIN, arg + i, 19))
			return (FALSE);
	}
	return (TRUE);
}
