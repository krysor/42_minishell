/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:57:36 by yaretel-          #+#    #+#             */
/*   Updated: 2023/04/25 15:00:59 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>
# include "../deps/ft/libft.h"

//this guy to open a file
#include <fcntl.h>

//These headers are required for the readline function
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//These headers are required for signal handling (CTRL + 'C'/ 'D' / '/')
# include <signal.h>
# include <termios.h>

//These headers are required for builtins
#include <dirent.h>

//Macro's for readline and main loop
# define CMD_EXIT 	"exit"
# define MSG_HELLO 	"Bonjournooo je suis un pika pika pikachuuuu en dis is SPARTA!!!! jk diz iz notre MINIseaSHELL\n"

//macro's for node->interprete
# define TRUE		1
# define FALSE		0

//macro's for invisible character
# define INVIS		24

//macro's for builtins
# define CD			"cd"
# define PWD		"pwd"
# define EXPORT		"export"
# define UNSET		"unset"
# define ENV		"env"
# define EXIT		"exit"

# define BUFFER_SIZE_PWD	100

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

typedef struct		s_rdr
{
	char			*type; // can be ">", ">>", "<", "<<" or NULL
	char			*file; // the file that comes after the redirection
	struct s_rdr	*next;
}					t_rdr;

typedef struct	s_cmd
{
	t_rdr		*rdr;
	char		*file; // a string pointing to the command executable, NULL if command is builtin
	int			(*builtin)(char *args[], char **envp[]); // a pointer to the builtin function, NULL if not a builtin function
	char		**args; // the arguments to pass to the command
}				t_cmd;

// These are all the functions in Minishell
char			*is_mchar(char *c);
char			*is_quote(char *c);
char			*is_operator(char *c);
//size_t			ft_strlen(const char *str);
void			mark_sequence(char *s, unsigned int amount, char marking);
char			*find_next(char *s);
char			*create_tokcod(char *cmd_line);
void			yikes(char *msg, unsigned int ac, ...);
size_t			strdlen(const char *s, const char *c);
char			*ft_get_env_val(char *envp[], char *env);
//int				ft_strncmp(const char *s1, const char *s2, size_t n);
//char			*ft_strdup(const char *s);
//void			ft_putstr_fd(char *s, int fd);
size_t			cstrlen(char c, char *s);
int				is_in_set(char c, const char *set);
unsigned int	add_token_node(t_token **start, t_token **head, char *pt, char *tokcod, unsigned int i);
t_token			*tokcod_to_list(char *pt, char *tokcod, int interprete, t_token *end);
t_token			*lex_it(char *pt, int interprete, t_token *end);
t_token			*tokcod_to_list(char *pt, char *tokcod, int interprete, t_token *end);
void			expand_toknode(t_token **node, t_token *prev, char *toknod, char **envp);
size_t			seqstrlen(char *seq, char *s);
void			mark_quotes(char *pt, size_t len, char *tokcod);
ssize_t			value_len_diff(char *dlr, char **envp);
char			*expand_var(char *dest, char *dollar, unsigned int *i, unsigned int *j, char **envp);
char			*strsquash(char x, const char *str);
void			mark_outer_quotes(char *pt, char *tokcod, char marking);
void			executor(t_cmd **lst, char **ep[]);
t_token			*expander(t_token *lst, char **envp);
char			*ft_getenv(char *ep[], char *name);
size_t 			strdlen(const char *s, const char *d);
int				set_cmd_builtin(t_cmd *cmd);
char			**arrdup(char **arr);
char			*ft_strins(char *str, unsigned int pos, char *ins);
char			*ft_strtake(char *str, unsigned int pos, size_t size);

//functions for the main and basic shell interface
void			init_shell(void);
void			ft_ctrl_c(int i);
int				line_is_not_CMD_EXIT(char *line);
char 			*get_line(char **envp);
char			*get_prompt(char **envp);
void			clean_shell(void);

//readline functions for the prompt
void			rl_clear_history (void);
void			rl_replace_line (const char *text, int clear_undo);
void			rl_keep_mark_active (void);
int				rl_on_new_line (void);

t_cmd			**parser(t_token *lst_tok, char **envp);

//parser and utils_parser functions
int				token_is_pipe(t_token *token);
int				set_cmd_default(t_cmd *arr, t_token *token);
int				update_cmd(t_token **lst_tok_pnt, t_token *lst_tok, t_cmd *cmd, char **envp);
int				token_is_operator(t_token *lst_tok);
int				handle_operator(t_token **lst_tok_pnt, t_cmd *arr);
char			*getpath(char *cmd, char **envp);

//redirection struct functions
t_rdr	*rdr_new(char *type, char *file);
t_rdr	*lst_rdr_last(t_rdr *lst_rdr);
void	lst_rdr_add(t_rdr **lst_rdr, t_rdr *rdr);

//frees all the stuff
void			free_lst_tok(t_token *lst);
void			free_arr_argv(t_cmd **arr_argv);
void			free_arr(char **arr);
void			free_intermediates(char *line, t_token *lst_tok, t_cmd **arr_cmd);

//for printing intermediate results; delete before final pushing
void			print_tokenlist(t_token *tokenlist_og);
void			print_arrcmd(t_cmd **arr);
void			print_rdr(t_rdr *rdr);

//builtins
int	ft_echo(char **args, char ***envp);
int	ft_cd(char **args, char ***envp);
int	ft_pwd(char **args, char ***envp);
int	get_i_var(char *var, char **envp);
int ft_export(char **args, char ***envp);
int	ft_export_var(char *arg, char ***envp_pnt);
int ft_unset(char **args, char ***envp);
void	ft_unset_var(char *arg, char ***envp_pnt);
int ft_env(char **args, char ***envp);
int ft_exit(char **args, char ***envp);

char	*find_var(char *str, size_t *size);
#endif
