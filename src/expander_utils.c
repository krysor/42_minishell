/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:38:05 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/08 09:35:23 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// returns pointer to the first character ('$') of
//		the formatted variable in the string and sets 'size' to
//			the number of characters of this variable
char	*find_var(char *str, size_t *size)
{
	if (!str || !size)
		return (NULL);
	*size = 0;
	while (*str && *str != '$')
		str++;
	if (*str == '$')
		*size = strdlen(str, " \t\n|<>");
	return (str);
}
