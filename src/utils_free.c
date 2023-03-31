/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:50:29 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/31 13:54:41 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lst_tok(t_token *lst)
{
	t_token	*temp;
	
	while (lst)
	{
		temp = lst->next;
		free(lst->token);
		free(lst);
		lst = temp;
	}
}

void	free_arr_argv(t_cmd **arr_argv)
{
	int			i;
	t_cmd	*temp;

	if (!arr_argv)
		return ;
	i = 0;
	while (arr_argv[i])
	{
		temp = arr_argv[i++];
		free(temp->file);
		free(temp->rdr);
		free_arr(temp->args);
		free(temp);	
	}
	free(arr_argv);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_intermediates(char *line, t_token *lst_tok, t_cmd **arr_cmd)
{
	free(line);
	free_lst_tok(lst_tok);
	free_arr_argv(arr_cmd);
}
