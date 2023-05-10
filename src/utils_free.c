/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:50:29 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/05/09 10:58:43 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_lst_rdr(t_rdr *rdr);

void	free_lst_tok(t_token *lst)
{
	t_token	*temp;

	while (lst)
	{
		temp = lst->next;
		dmy_free(lst->token);
		dmy_free(lst);
		lst = temp;
	}
}

void	free_arr_argv(t_cmd **arr_argv)
{
	int		i;
	t_cmd	*temp;

	if (arr_argv == NULL)
		return ;
	i = 0;
	while (arr_argv[i])
	{
		temp = arr_argv[i++];
		free_lst_rdr(temp->rdr);
		dmy_free(temp->file);
		free_arr(temp->args);
		dmy_free(temp);
	}
	dmy_free(arr_argv);
}

static void	free_lst_rdr(t_rdr *rdr)
{
	t_rdr	*temp;

	if (!rdr)
		return ;
	while (rdr)
	{
		temp = rdr->next;
		dmy_free(rdr->type);
		dmy_free(rdr->file);
		dmy_free(rdr);
		rdr = temp;
	}
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		dmy_free(arr[i++]);
	dmy_free(arr);
}

void	free_intermediates(char *line, t_token *lst_tok, t_cmd **arr_cmd)
{
	free(line);//dmy_free(line);
	free_lst_tok(lst_tok);
	free_arr_argv(arr_cmd);
}
