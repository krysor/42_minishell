/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:57:36 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/16 12:27:42 by kkaczoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "../deps/ft/libft.h"

//These headers are required for the readline function
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//These headers are required for signal handling (CTRL + 'C'/ 'D' / '/')
# include <signal.h>
# include <termios.h>

//Macro's for readline and main loop
# define CMD_EXIT 	"exit"
# define MSG_HELLO 	"Bonjournooo je suis un pika pika pikachuuuu en dis is SPARTA!!!! jk diz iz notre MINIseaSHELL\n"

//This struct is used to make a linked list of all the words and tokens during the lexer stage
typedef struct	s_token
{
	char			*token;
	struct s_token	*next;
}				t_token;

typedef struct	s_envvar
{
	size_t			len;
	char			*value;
	struct s_envvar	*next;
}				t_envvar;

//These definitions are used for the t_lex.type members
# define WORD 	0
# define TOKEN 	1

// These are all the functions in Minishell
char	*is_mchar(char *c);
char	*is_quote(char *c);
char	*is_operator(char *c);
size_t	ft_strlen(const char *str);
void	mark_sequence(char *s, unsigned int amount, char marking);
char	*find_next(char *s);
char	*create_tokcod(char *cmd_line);
void	yikes(char *msg, unsigned int ac, ...);
size_t	strclen(const char *s, char c);
t_token	*create_tokenlist(char *pt, char *tokcod);

void	rl_clear_history (void);
void	rl_replace_line (const char *text, int clear_undo);
void	rl_keep_mark_active (void);
int		rl_on_new_line (void);

#endif
