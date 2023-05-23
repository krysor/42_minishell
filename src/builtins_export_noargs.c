/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_noargs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:59:30 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/23 11:23:10 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	swap(char **one, char **two)
{
	char	*temp;

	temp = *one;
	*one = *two;
	*two = temp;
}

static int	unsorted(char *first, char *last)
{
	size_t	firstlen;
	size_t	lastlen;
	size_t	biggest;

	if (last == NULL || first == NULL)
		return (0);
	firstlen = ft_strlen(first);
	lastlen = ft_strlen(last);
	if (firstlen > lastlen)
		biggest = firstlen;
	else
		biggest = lastlen;
	if (ft_strncmp(last, first, biggest) > 0)
		return (0);
	else
		return (1);
}

static void	sort_arr(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (unsorted(envp[i], envp[i + 1]))
		{
			swap(&envp[i], &envp[i + 1]);
			i = 0;
		}
		i++;
	}
}

static void	write_env_export_format(char *kv)
{
	int	kl;

	kl = strdlen(kv, "=");
	write(STDOUT_FILENO, "declare -x ", 11);
	write(STDOUT_FILENO, kv, kl);
	write(STDOUT_FILENO, "=\"", 2);
	write(STDOUT_FILENO, kv + kl + 1, ft_strlen(kv + kl + 1));
	write(STDOUT_FILENO, "\"\n", 2);
}

int	ft_export_noargs(char *envp_og[])
{
	char	**envp;
	int		i;

	envp = arrdup(envp_og);
	if (!envp)
		return (1);
	sort_arr(envp);
	sort_arr(envp);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_=", 2) == 0)
		{
			i++;
			continue ;
		}
		write_env_export_format(envp[i]);
		i++;
	}
	free_arr(envp);
	return (0);
}
