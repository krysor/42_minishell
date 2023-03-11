/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:57:36 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/11 09:49:37 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

//This struct is used to make a linked list of all the words and tokens during the lexer stage
typedef struct	s_lex
{
	int				type;
	char			*content;
	struct s_lex	*next;
}				t_lex;

//These definitions are used for the t_lex.type members
# define WORD 	0
# define TOKEN 	1

// These are all the functions in Minishell

char	*is_mchar(char *c);
char	*is_quote(char *c);
size_t	ft_strlen(const char *str);
void	mark_sequence(char *s, unsigned int amount, char marking);
char	*find_next(char *s);
char	*create_wrdcod(char *cmd_line);
void	yikes(char *msg, unsigned int ac, ...);

#endif
