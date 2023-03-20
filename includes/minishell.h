/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:57:36 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/20 11:09:48 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
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

//macro's for node->interprete
# define TRUE		1
# define FALSE		0

//This struct is used to make a linked list of all the words and tokens during the lexer stage
typedef struct	s_token
{
	char			*token;
	int				interprete;
	struct s_token	*next;
}				t_token;

typedef struct	s_envvar
{
	size_t			len;
	char			*value;
	struct s_envvar	*next;
}				t_envvar;

// These are all the functions in Minishell
char			*is_mchar(char *c);
char			*is_quote(char *c);
char			*is_operator(char *c);
size_t			ft_strlen(const char *str);
void			mark_sequence(char *s, unsigned int amount, char marking);
char			*find_next(char *s);
char			*create_tokcod(char *cmd_line);
void			yikes(char *msg, unsigned int ac, ...);
size_t			strdlen(const char *s, const char *c);
char			*ft_get_env_val(char *envp[], char *env);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *s);
void			ft_putstr_fd(char *s, int fd);
size_t			cstrlen(char c, char *s);
int				is_in_set(char c, const char *set);
unsigned int	add_token_node(t_token **start, t_token **head, char *pt, char *tokcod, unsigned int i);
t_token			*tokcod_to_list(char *pt, char *tokcod, int interprete, t_token *end);
t_token			*lex_it(char *pt, int interprete, t_token *end);
t_token			*tokcod_to_list(char *pt, char *tokcod, int interprete, t_token *end);
void			expand_node(t_token *node, t_token *prev);
size_t			seqstrlen(char *seq, char *s);
void			mark_quotes(char *pt, size_t len, char *tokcod);
void			rl_clear_history (void);
void			rl_replace_line (const char *text, int clear_undo);
void			rl_keep_mark_active (void);
int				rl_on_new_line (void);

#endif
