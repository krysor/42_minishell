/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:28:30 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/30 17:35:40 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_nb_tokens_before_pipe(t_token *lst_tok);

int	set_cmd_default(t_command *arr, t_token *token)
{
	int	nb_tokens_before_pipe;
	
	arr->file = NULL;
	arr->builtin = NULL;
	arr->rdr = NULL;//possibly needs correction if contents of rdr struct change
	nb_tokens_before_pipe = get_nb_tokens_before_pipe(token);
	//printf("nb_tokens_before_pipe: %d\n", nb_tokens_before_pipe);
	arr->args = malloc(sizeof(char *) * (nb_tokens_before_pipe + 1));
	if (!arr->args)
		return (1);
	arr->args[nb_tokens_before_pipe] = NULL;
	return (0);
}

static int	get_nb_tokens_before_pipe(t_token *lst_tok)
{
	int		nb;
	t_token	*temp;

	nb = 0;
	temp = lst_tok;
	while (temp && !token_is_pipe(temp))
	{
		nb++;
		temp = temp->next;
	}
	return (nb);
}

int	is_token_operator(char *str)
{
	int	len;
	
	if (!is_operator(str))
		return (0);
	len = ft_strlen(str);
	if (len == 1)
		return (1);
	else if (len == 2
		&& (str[1] == '<' || str[1] == '>'))
		return (1);
	return (0);
}

//decalre a pnt to a pnt one scope outside the loop
void	handle_operator(t_token *token, t_command *arr)
{	
	(void)arr;
	if (*token->token == '|')
		printf("pipe\n");//pipe overpowers input rediretction BUT NOT OUTPUT REDIRECTION
	else if (*token->token == '<')
		printf("input: %s\n", token->next->token);
	else if (*token->token == '>')
		printf("output: %s\n", token->next->token);
}
