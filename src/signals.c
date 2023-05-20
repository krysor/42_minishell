/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:39 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/20 17:28:28 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ctrl_c(int i)
{
	(void)i;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = 1;
}

void	ft_ctrl_c_main_prompt(int i)
{
	(void)i;
	g_exit_code = 1;
}

void	ft_ctrl_c_exit(int i)
{
	(void)i;
	exit(1);
}

void	ft_ctrl_c_child(int i)
{
	(void)i;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_ctrl_slash_child(int i)
{
	(void)i;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}
