/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:51:12 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/03/28 15:01:32 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_nb_pipes(t_token	*lst_tok);
void	set_arr(t_command **arr, int nb_cmd, t_token *lst_tok);
int		token_is_pipe(t_token *token);
int		set_cmd(t_command *arr, t_token *token);
int		set_cmd_default(t_command *arr, t_token *token);
int		get_nb_tokens_before_pipe(t_token *lst_tok);

t_command	**parser(t_token	*lst_tok)
{
	int			nb_cmd;
	t_command	**arr;

	if (!lst_tok)
		return (NULL);
	nb_cmd = get_nb_pipes(lst_tok) + 1;
	arr = malloc(sizeof(t_command *) * (nb_cmd + 1));
	if (!arr)
		return (NULL);//some special quitting here?
	//arr[0] = NULL;
	arr[nb_cmd] = NULL;
	set_arr(arr, nb_cmd, lst_tok);
	return (arr);
}

int	get_nb_pipes(t_token *lst_tok)
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

int	token_is_pipe(t_token *token)
{
	if (token
		&& token->interprete == TRUE
		&& token->token[0] == '|'
		&& ft_strlen(token->token) == 1)
		return (1);
	return (0);
}

void	set_arr(t_command **arr, int nb_cmd, t_token *lst_tok)
{
	int		i;

	(void)lst_tok;

	i = 0;
	while (i < nb_cmd)
	{
		arr[i] = malloc(sizeof(t_command));
		if (!arr[i]->args || set_cmd(arr[i], lst_tok))
			break ;//some freeing necessary here
		i++;
	}
}

int	is_fname(char *str)
{
	if (!is_operator(str))
		return (0);
	if (ft_strlen(str) == 1)
		return (1);
	else if (ft_strlen(str) == 2
		&& (str[1] == '<' || str[1] == '>'))
		return (1);
	return (0);
}

//solve: segfault with "|" as only input
int	set_cmd(t_command *arr, t_token *token)
{
	//int	i;
	
	if (set_cmd_default(arr, token))
		return (1);
	//i = 0;
	while (token && !token_is_pipe(token))
	{
		//check if meta
		
		printf("before if\n");
		if (token->interprete && is_fname(token->token))
			printf("redirection stuff?\n");
		//	if yes look at the next one

		//else check if first
		//	if yes look for file name

		//else add to arg list
		//	to the argv[]
		
		
		// if (token->interprete)
		// 	interprete_token(arr, token);
		// else if (!i)
		// 	set_cmd_file(arr, token);
		// here gotta add statements to fill in all cmd struct elements
		
		token = token->next;
	}
	if (token && token->next)
		token = token->next;
	return (0);
}

int	set_cmd_default(t_command *arr, t_token *token)
{
	int	nb_tokens_before_pipe;
	
	arr->file = NULL;
	arr->builtin = NULL;
	nb_tokens_before_pipe = get_nb_tokens_before_pipe(token);
	arr->args = malloc(sizeof(char *) * (nb_tokens_before_pipe + 1));
	if (!arr->args)
		return (1);
	arr->args[nb_tokens_before_pipe] = NULL;
	arr->input.fd = STDIN_FILENO;
	arr->input.flag = 0;
	arr->output.fd = STDOUT_FILENO;
	arr->output.flag = O_CREAT | O_TRUNC;//possibly need different flags
	return (0);
}

int	get_nb_tokens_before_pipe(t_token *lst_tok)
{
	int		nb;
	t_token	*temp;

	nb = 0;
	temp = lst_tok;
	while (token_is_pipe(temp))
	{
		nb++;
		temp = temp->next;
	}
	return (nb);
}
