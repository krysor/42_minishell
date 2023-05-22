/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_update_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:28:09 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/28 17:28:11 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_cmd_builtin(t_cmd *cmd)
{
	char	*function;
	size_t	len;

	if (!cmd->args || !cmd->args[0])
		return (0);
	function = cmd->args[0];
	len = ft_strlen(function);
	if (!ft_strncmp(function, "echo", len) && len == ft_strlen("echo"))
		cmd->builtin = &ft_echo;
	else if (!ft_strncmp(function, CD, len) && len == ft_strlen(CD))
		cmd->builtin = &ft_cd;
	else if (!ft_strncmp(function, PWD, len) && len == ft_strlen(PWD))
		cmd->builtin = &ft_pwd;
	else if (!ft_strncmp(function, EXPORT, len) && len == ft_strlen(EXPORT))
		cmd->builtin = &ft_export;
	else if (!ft_strncmp(function, UNSET, len) && len == ft_strlen(UNSET))
		cmd->builtin = &ft_unset;
	else if (!ft_strncmp(function, ENV, len) && len == ft_strlen(ENV))
		cmd->builtin = &ft_env;
	else if (!ft_strncmp(function, EXIT, len) && len == ft_strlen(EXIT))
		cmd->builtin = &ft_exit;
	else
		return (1);
	return (0);
}

int	invalid_nb_cmd(int nb_cmd)
{
	if (nb_cmd < 0)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR_FILENO);
		g_exit_code = 258;
		return (1);
	}
	if (nb_cmd > NB_CMD_MAX)
	{
		ft_putstr_fd("too many commands as input\n", STDERR_FILENO);
		g_exit_code = 1;
		return (1);
	}
	return (0);
}
