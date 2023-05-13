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

// inserts string 'ins' at index 'pos' in 'str'
char	*ft_strins(char **str, unsigned int pos, char *ins)
{
	char	*new;
	size_t	strlen;
	size_t	inslen;

	if (!str || !(*str))
		return (NULL);
	if (!ins)
		return (*str);
	strlen = ft_strlen(*str);
	inslen = ft_strlen(ins);
	new = (char *)dmy_malloc(sizeof(*new) * strlen + inslen + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, *str, pos + 1);
	ft_strlcpy(new + pos, ins, inslen + 1);
	ft_strlcpy(new + pos + inslen, *str + pos, strlen + 1);
	dmy_free(*str);
	*str = new;
	return (new);
}

// takes substring at index 'pos' of size 'size' in string 'str' 
//		and removes it from the string
char	*ft_strtake(char **str, unsigned int pos, size_t size)
{
	char	*new;
	size_t	strlen;

	if (!str || !(*str) || size == 0)
		return (NULL);
	strlen = ft_strlen((*str));
	new = (char *)dmy_malloc(sizeof(*new) * (strlen - size + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, (*str), pos + 1);
	if (pos + size < strlen)
		ft_strlcpy(new + pos, (*str) + pos + size, strlen);
	dmy_free(*str);
	*str = new;
	return (new);
}

char	*tokcodadjust(char **tokcod, unsigned int pos, ssize_t correction)
{
	if (!tokcod || !(*tokcod))
		return (NULL);
	if (correction == 0)
		return (*tokcod);
	while (correction-- > 0)
		ft_strins(tokcod, pos, &(char []){(*tokcod)[pos], '\0'}[0]);
	if (correction < 0)
		ft_strtake(tokcod, pos, correction * -1);
	return (*tokcod);
}
