/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:49:39 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/07 18:07:04 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokenlist(t_token *tokenlist_og)
{
	unsigned int	i;
	t_token 		*tokenlist;

	i = 0;
	tokenlist = tokenlist_og;
	while (tokenlist)
	{
		printf("%i)\taddress: %p\ttoken: %s\tinterprete: %i\tnext: %p\n", i, tokenlist, tokenlist->token, tokenlist->interprete, tokenlist->next);
		tokenlist = tokenlist->next;
		i++;
	}
}

void	print_arrcmd(t_cmd **arr)
{
	int	i;
	int	j;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("cmd[%d]:\n", i);
		printf("cmd[%d]->file\t: %s\n", i, arr[i]->file);
		printf("cmd[%d]->builtin\t: %p\n", i, arr[i]->builtin);
		printf("cmd[%d]->rdr:\n", i);
		print_rdr(arr[i]->rdr);
		j = -1;
		printf("cmd[%d]->args\t\n", i);
		while (arr[i]->args[++j])
			printf("\tcmd[%d]->args[%d]\t: %s\n", i, j, arr[i]->args[j]);
		printf("\n");
		i++;
	}
}

void	print_rdr(t_rdr *rdr)
{
	t_rdr	*temp;
	
	temp = rdr;
	//printf("here or nah?\n");
	while (temp)
	{
		printf("\tnode:%p\n", temp);
		printf("\t\ttype: %s\n", temp->type);
		printf("\t\tfile: %s\n", temp->file);
		temp = temp->next;
	}
}
