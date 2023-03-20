/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:51:12 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/20 17:03:16 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_nb_pipes(t_token	*lst_tok);
void	set_arr(t_command **arr, int nb_cmd, t_token *lst_tok);

t_command	**parser(t_token	*lst_tok)
{
	int			nb_cmd;
	t_command	**arr;

	if (!lst_tok)
		return (NULL);
	nb_cmd = get_nb_pipes(lst_tok) + 1;
	arr = malloc(sizeof(t_command *) * nb_cmd + 1);
	if (!arr)
		return (NULL);//some special quitting here?

	set_arr(arr, nb_cmd, lst_tok);
	
	arr[nb_cmd] = NULL;
	return (arr);
}

int	token_is_pipe(t_token *token)
{
	if (token->interprete
		&& token->token[0] == '|'
		&& ft_strlen(token->token) == 1)
		return (1);
	return (0);
}

int	get_nb_pipes(t_token	*lst_tok)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = lst_tok;
	while (temp)
	{
		if (token_is_pipe(temp))
			i++;
		temp = temp->next;
	}
	return (i);
}

int	get_nb_tokens_before_pipe(t_token *lst_tok)
{
	int		nb;
	t_token	*temp;

	nb = 0;
	temp = lst_tok;
	while (temp && token_is_pipe(temp))
	{
		nb++;
		temp = temp->next;
	}
	return (nb);
}

void	set_arr(t_command **arr, int nb_cmd, t_token *lst_tok)
{
	int		i;
	t_token	*temp;

	(void)nb_cmd;

	i = 0;
	temp = lst_tok;
	while (arr[i])
	{
		arr[i]->args = malloc(sizeof(char *) *
			(get_nb_tokens_before_pipe(lst_tok) + 1));
		if (!arr[i]->args)
			break ;//some freeing necessary here
		//here a function that will complete arr[i] and move temp
		i++;
	}
}

