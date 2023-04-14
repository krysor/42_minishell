/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:06:42 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/14 11:08:58 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_token	*expander(t_token *lst)
{
	char	*tokcod;

	while (lst)
	{
		tokcod = create_tokcod(lst->token);
		mark_outer_quotes(lst->token, tokcod, -1);
		expand_toknode(&lst, prev, tokcod);
		free(tokcod);
		prev = lst;
		lst = lst->next;
	}
}
