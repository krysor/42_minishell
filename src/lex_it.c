/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_it.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:14:48 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/20 11:39:03 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*lex_it(char *pt, int interprete, t_token *end)
{
	char	*tokcod;
	t_token	*new;

	tokcod = create_tokcod(pt);
	new = tokcod_to_list(pt, tokcod, interprete, end);
	free(tokcod);
	return (new);
}
