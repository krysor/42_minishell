/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:57:36 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/23 10:27:04 by kkaczoro         ###   ########.fr       */
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
# include "../deps/dmy/includes/dmy.h"
# include <errno.h>

//These headers are required for the readline function
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//These headers are required for signal handling (CTRL + 'C'/ 'D' / '/')
# include <signal.h>
# include <termios.h>

//These headers are required for builtins
# include <dirent.h>

//Macro's for readline and main loop
# define CMD_EXIT 	"exit\n"
# define MSG_HELLO 	"Bonjournooo je suis un pika pika pikachuuuu en dis is SPARTA!!!!\n\
					jk diz iz notre MINIseaSHELL\n"

//macro's for pipe
# define READ		0
# define WRITE		1

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

//macro's for getcwd
# define BUFFER_SIZE_PWD		100
# define BUFFER_SIZE_PWD_MAX	1000

//macro's for exit
# define STR_LONG_MIN		"9223372036854775808"
# define STR_LONG_MAX		"9223372036854775807"

//macro's for get_next_line
# define BUFFER_SIZE		1000

//macro's for remove quotes
# define ERR_MSG_RM_QUOTES	"error: quoted area of smaller than 2 chars found\n"
# define ERR_MSG_RM_QUOTES_COUNT	50

//macro's for empty string
# define EMPTY_STR			"V3r1-uN1qU3-sTr"

//macro's for the maximum number of commands
# define NB_CMD_MAX			500

extern int	g_exit_code;

//This struct is used to make a linked list of
//	all the words and tokens during the lexer stage
typedef struct s_token
{
	char			*token;
	int				interprete;
	struct s_token	*next;
}				t_token;

typedef struct s_envvar
{
	size_t			len;
	char			*value;
	struct s_envvar	*next;
}				t_envvar;

typedef struct s_rdr
{
	char			*type;
	char			*file;
	struct s_rdr	*next;
}					t_rdr;

typedef struct s_cmd
{
	t_rdr		*rdr;
	char		*file;
	int			(*builtin)(char *args[], char **envp[]);
	char		**args;
	int			fd_in;
	int			fd_out;
}				t_cmd;

// These are all the functions in Minishell
char			*is_mchar(char *c);
char			*is_quote(char *c);
char			*is_operator(char *c);
void			mark_sequence(char *s, unsigned int amount, char marking);
char			*find_next(char *s);
char			*create_tokcod(char *cmd_line);
void			yikes(char *msg, unsigned int ac, ...);
size_t			strdlen(const char *s, const char *c);
char			*ft_get_env_val(char *envp[], char *env);
size_t			cstrlen(char c, char *s);
int				is_in_set(char c, const char *set);
t_token			*tokcod_to_list(char *pt, char *tokcod,
					int interprete, t_token *end);
t_token			*lex_it(char *pt, int interprete, t_token *end);
t_token			*tokcod_to_list(char *pt, char *tokcod,
					int interprete, t_token *end);
void			expand_toknode(t_token **node, t_token *prev,
					char **toknod, char **envp);
size_t			seqstrlen(char *seq, char *s);
void			mark_quotes(char *pt, size_t len, char *tokcod);
ssize_t			value_len_diff(char *dlr, char **envp);
char			*strsquash(char x, const char *str);
void			mark_outer_quotes(char *pt, char *tokcod, char marking);

//executor
void			executor(t_cmd **lst, char **ep[]);
void			handle_redirections(t_cmd **lst);
void			process_redirections(t_cmd *cmd);
void			close_open_fds(t_cmd **lst);
pid_t			prepare_and_exec(t_cmd *cmd, char *ep[],
					int next, int *fd_read_prev);

char			*get_next_line(int fd);
char			*ft_getenv(char *ep[], char *name);
char			**arrdup(char **arr);
char			*get_path(char *cmd, char **envp);

t_token			*expander(t_token *lst, char **envp);
size_t			strdlen(const char *s, const char *d);
int				set_cmd_builtin(t_cmd *cmd);
char			*ft_strins(char **str, unsigned int pos, char *ins);
char			*ft_strtake(char **str, unsigned int pos, size_t size);

//functions for the main and basic shell interface
int				update_shellvl(char **envp[]);
int				init_shell(char **envp[]);
void			ft_ctrl_c(int i);
void			ft_ctrl_c_main_prompt(int i);
void			ft_ctrl_c_child(int i);
void			ft_ctrl_c_exit(int i);
void			ft_ctrl_slash_child(int i);
int				line_is_not_CMD_EXIT(char *line);
char			*get_line(void);
char			*get_prompt(char **envp);

//readline functions for the prompt
void			rl_clear_history(void);
void			rl_replace_line(const char *text, int clear_undo);
void			rl_keep_mark_active(void);
int				rl_on_new_line(void);

//parser and utils_parser functions
t_cmd			**parser(t_token *lst_tok, char **envp);
int				get_nb_pipes(t_token *lst_tok);
int				invalid_nb_cmd(int nb_cmd);
int				token_is_pipe(t_token *token);
int				get_nb_tokens_before_pipe(t_token *lst_tok);
int				token_is_operator(t_token *lst_tok);
int				handle_operator(t_token **lst_tok_pnt, t_cmd *arr);

//redirection struct functions
t_rdr			*lst_rdr_last(t_rdr *lst_rdr);
void			lst_rdr_add(t_rdr **lst_rdr, t_rdr *rdr);
t_rdr			*rdr_new(char *type, char *file);

//frees all the stuff
void			free_lst_tok(t_token *lst);
void			free_arr_argv(t_cmd **arr_argv);
void			free_arr(char **arr);
void			free_intermediates(char **line_pnt,
					t_token **lst_tok_pnt, t_cmd ***arr_cmd_pnt);

//for printing intermediate results; delete before final pushing
void			print_tokenlist(t_token *tokenlist_og);
void			print_arrcmd(t_cmd **arr);
void			print_rdr(t_rdr *rdr);

//builtins
int				ft_echo(char **args, char ***envp);
int				ft_pwd(char **args, char ***envp);
char			*ft_getcwd(void);
int				get_i_var(char *var, char **envp);
int				ft_cd(char **args, char ***envp);
int				ft_export(char **args, char ***envp);
int				ft_export_noargs(char *envp_og[]);
int				ft_export_var(char **arg_pnt, char ***envp_pnt);
int				ft_unset(char **args, char ***envp);
void			ft_unset_var(char *arg, char ***envp_pnt);
int				ft_env(char **args, char ***envp);
int				ft_exit(char **args, char ***envp);
int				get_exit_code(char **args);
long int		ft_atolong(const char *nptr);
int				ft_isspace(char chr);
int				ft_nbdigit(char *s);

char			*find_var(char *str, size_t *size);
char			*create_varcod(char *tokcod, char *pt);
int				remove_quotes(char **tokcod, char **pt);
char			*expand_token(char **envp, char **tokcod, char **token);
char			*tokcodadjust(char **str, unsigned int pos, ssize_t correction);

#endif
