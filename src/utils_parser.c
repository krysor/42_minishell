/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:28:30 by kkaczoro          #+#    #+#             */
/*   Updated: 2023/04/07 18:00:09 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_nb_tokens_before_pipe(t_token *lst_tok);
static int	set_cmd_builtin(t_cmd *cmd);

// Sets default values for all the fields of a a t_cmd struct.
int	set_cmd_default(t_cmd *arr, t_token *token)
{
	int	nb_tokens_before_pipe;
	
	arr->file = NULL;
	arr->builtin = NULL;
	arr->rdr = NULL;
	nb_tokens_before_pipe = get_nb_tokens_before_pipe(token);
	arr->args = malloc(sizeof(char *) * (nb_tokens_before_pipe + 1));
	if (!arr->args)
		return (1);
	arr->args[nb_tokens_before_pipe] = NULL;
	return (0);
}

int	update_cmd(t_token **lst_tok_pnt, t_token *lst_tok, t_cmd *cmd)
{
	int	i;
	
	i = 0;
	while (lst_tok && !token_is_pipe(lst_tok))
	{
		if (token_is_operator(lst_tok))
		{
			if (handle_operator(&lst_tok, cmd))
				return (1);
		}
		else
		{
			cmd->args[i] = ft_strdup(lst_tok->token);
			if (!cmd->args[i])
				return (1);
			i++;
		}
		lst_tok = lst_tok->next;
	}
	*lst_tok_pnt = lst_tok;
	cmd->args[i] = NULL;
	if (cmd->args[0] && set_cmd_builtin(cmd))
		cmd->file = getpath(cmd->args[0]);
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

int	token_is_operator(t_token *lst_tok)
{
	int		len;
	char	*token;

	token = lst_tok->token;
	if (!is_operator(token) || !lst_tok->interprete)
		return (0);
	len = ft_strlen(token);
	if (len == 1)
		return (1);
	else if (len == 2
		&& (token[1] == '<' || token[1] == '>'))
		return (1);
	return (0);
}

//decalre a pnt to a pnt one scope outside the loop
int	handle_operator(t_token **lst_tok_pnt, t_cmd *arr)
{	
	t_token	*lst_tok;
	char	*token;
	t_rdr	*rdr;
	
	if (!lst_tok_pnt || !*lst_tok_pnt || !arr)
		return (1);
	lst_tok = *lst_tok_pnt;
	token = lst_tok->token;
	if (lst_tok->next && (*token == '<' || *token == '>'))
	{
		rdr = rdr_new(token, lst_tok->next->token);
		if (!rdr)
			return (1);
		lst_rdr_add(&arr->rdr, rdr);
	}
	*lst_tok_pnt = lst_tok->next;
	return (0);
}

static int	set_cmd_builtin(t_cmd *cmd)
{
	char	*function;
	size_t	len;
	
	if (!cmd->args || !cmd->args[0])
		return (0);
	function = cmd->args[0];
	len = ft_strlen(function);
	if (!ft_strncmp(function, "echo", len) && len == ft_strlen("echo"))
		cmd->builtin = &ft_echo;
	else if (!ft_strncmp(function, CD, len) && len == ft_strlen(CD))
		cmd->builtin = &ft_cd;
	else if (!ft_strncmp(function, PWD, len) && len == ft_strlen(PWD))
		cmd->builtin = &ft_pwd;
	else if (!ft_strncmp(function, EXPORT, len) && len == ft_strlen(EXPORT))
		cmd->builtin = &ft_export;
	else if (!ft_strncmp(function, UNSET, len) && len == ft_strlen(UNSET))
		cmd->builtin = &ft_unset;
	else if (!ft_strncmp(function, ENV, len) && len == ft_strlen(ENV))
		cmd->builtin = &ft_env;
	else if (!ft_strncmp(function, EXIT, len) && len == ft_strlen(EXIT))
		cmd->builtin = &ft_exit;
	else
		return (1);
	return (0);
}