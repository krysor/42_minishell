/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:57:36 by yaretel-          #+#    #+#             */
/*   Updated: 2023/03/14 14:41:19 by yaretel-         ###   ########.fr       */
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

//Macro's for readline and main loop
# define CMD_EXIT 	"exit"

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

char	*ft_get_env_val(char *envp[], char *env);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
void	ft_putstr_fd(char *s, int fd);

#endif
