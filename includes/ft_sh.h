/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 08:00:31 by eliu              #+#    #+#             */
/*   Updated: 2018/06/20 08:26:26 by eliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include "ast.h"
# include "libft.h"
# include "ft_printf.h"
# include "ft_prompt.h"
# include <termcap.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>

# define TERM_FD g_shell->term.fd

/*
** Function-y macros for terminal and cursor manipulation.
*/

# define OPCHAR(x) (x == '|' || x == '&' || x == ';' || x == '!')
# define REDIR_CHAR(x) (x == '>' || x == '<')

extern char				**g_environ;

typedef struct			s_shell
{
	t_term				term;
	char				*prompt_string;
	char				**temp_args;
}						t_shell;

void					update_size(t_term *t);
void					restore_defaults(t_term *t);

void					shell_init(void);
void					prompt(t_shell *s);
void					parse_commands(t_shell *s, char *buf);

/*
** Builtins
*/

enum					e_builtin
{
	BIN_ECHO,
	BIN_CD,
	BIN_ENV,
	BIN_SETENV,
	BIN_UNSETENV,
	NUM_HANDLED_BUILTINS
};

typedef void			t_builtin(char **args);

extern char				*g_builtin_str[NUM_HANDLED_BUILTINS];
extern t_builtin		*g_builtins_dispatch[NUM_HANDLED_BUILTINS];

t_builtin				g_builtin_cd;
t_builtin				g_builtin_env;
t_builtin				g_builtin_setenv;
t_builtin				g_builtin_unsetenv;
t_builtin				g_builtin_echo;

/*
** Parser Functions
*/

# define PARSE_ERROR -2
# define NOT_OP -1

char					**split_args(char *format);
char					*find_next(int *i, char *format, int end, char *tmp);

int						op_error_handle(char *c);
int						is_op(char *c);
int						op_len(char *c);
t_ast					*ast_init(void);
t_redir					*rdir_init(void);
int						is_shovel(char *format, int i);
char					**st_strptrnew(size_t size);
int						is_all_space(char *format, int i);
void					st_init(int *i, int *k, int *hold);
int						skip_char(char *format, int *i, char c);

/*
** Tokenizer Functions
*/

int						*tokenize(char **format);
int						is_operator(char *arg);
int						is_command(char *arg);
# define DQUOTE '\"'
# define QUOTE '\''
# define BQUOTE '`'
# define SUBSH '('
# define NEWLINE '\\'
# define DQUOTE_PROMPT "dquote> "
# define QUOTE_PROMPT "quote> "
# define BQUOTE_PROMPT "bquote> "
# define SUBSH_PROMPT "subsh> "
# define NEWLINE_PROMPT "> "

/*
** HELPERS_PARSER.c
*/

int						cont_nbr_backslashes(char *str, int i);
char					*get_type_prompt(char value);
void					cont_chars_capsules(char *str, char schar, int *cont);
char					*ft_strjoin_newline(char const *s1, char const *s2);

/*
** PARSE_LINE.c
*/

char					*concatinated_string(char type);
void					is_capsule_incomplete(char *str, char **temp);
char					*parse_line(char *str);

/*
** BRACKETS_PARSE_LINE.c
*/

int						syntax_error(char *str);

/*
** General utility functions
*/

size_t					ft_strlens(char **strings, int *pcount);
char					*ft_atos(char **strings);
int						arr_length(char **a);
int						ft_strspacecmp(char *s1, char *s2);
void					ft_lstaddback(t_list **lst, t_list *add);
char					*ft_strjoinv(int nstr, char *sep, ...);
void					ft_strcpy_2d(char **dst, char **src);
char					**ft_strdup_2d(char **src);
void					ft_swap_str(char **s1, char **s2);
char					*ft_get_env(char *name, char **env);
void					add_env_entry(char *entry);
void					ft_set_env(char *name, char *val, char **env);
void					free_string_array(char **ary);
#endif
