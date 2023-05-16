/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:31:57 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/10 15:18:40 by kkaczoro         ###   ########.fr       */
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

	ft_putstr_fd(CMD_EXIT, STDOUT_FILENO);
	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		exit_code = 256;
	}
	else if (args[1] == NULL)
		exit_code = 0;
	else if (arg_is_correct(args[1]) == FALSE)
	{
		ft_putstr_fd("exit: ", STDOUT_FILENO);
		ft_putstr_fd(args[1], STDOUT_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
		exit_code = 255;
	}
	else
		exit_code = ft_atolong(args[1]) % 256;
	return (exit_code);
}

static int	arg_is_correct(char *arg)
{
	int	i;

	while (ft_isspace(*arg))
		arg++;
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i] == '0')
		i++;
	if (arg_is_long(arg, i) == FALSE)
		return (FALSE);
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i] != '\0')
		return (FALSE);
	return (TRUE);
}

static int	arg_is_long(char *arg, int i)
{
	int	nb_digits;

	nb_digits = ft_nbdigit(arg + i);
	if (nb_digits > 19)
		return (FALSE);
	if (nb_digits == 19)
	{
		if (arg[0] == '-'
			&& ft_strncmp(STR_LONG_MIN, arg + i, 19) < 0)
			return (FALSE);
		if ((arg[0] == '+' || ft_isdigit(arg[0]))
			&& ft_strncmp(STR_LONG_MAX, arg + i, 19) < 0)
			return (FALSE);
	}
	return (TRUE);
}
