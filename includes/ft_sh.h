#ifndef FT_SH_H
# define FT_SH_H

# include "ast.h"
# include "libft.h"
# include "ft_printf.h"
# include "ft_prompt.h"
# include <termcap.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <assert.h>

# define TERM_FD g_shell->term.fd

/*
** Function-y macros for terminal and cursor manipulation.
*/

# define _term_do(x) tputs(tgetstr(x, NULL), 1, ft_weirdchar)
# define _goto(x, y) tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_weirdchar)
# define _put(x) ft_putstr_fd(x, TERM_FD)
# define _op(x) (x == '|' || x == '&' || x == ';')
# define _redir(x) (x == '>' || x == '<')

/*
** Structs
*/

/*
** Declaration of environ.
** Contains environment variables in the form:
** NAME=VAL
*/

extern char				**environ;

typedef struct			s_shell
{
	t_term				term;
	char				*prompt_string;
	char				**temp_args;
}						t_shell;

/*
** Global pointer for signal handling.
** For future development.
*/

t_shell					g_shellinit;
t_shell					*g_shell;

/*
** Function declarations:
*/

void					update_size(t_term *t);
void					restore_defaults(t_term *t);

void					shell_init(void);
void					prompt(t_shell *s);
void					parse_commands(t_shell *s, char *buf);

/*
** Builtin Function Declarations.
*/

int						run_builtin(int id, char **args);
int						is_builtin(char *str);

int						ftsh_cd(char **args);
int						ftsh_help(char **args);
int						ftsh_exit(char **args);

/* Parser Functions */

char					**split_args(char *format);
char					*find_next(int *i, char *format, int end, char *tmp);

int						is_op(char *c);
int						op_len(char *c);
t_ast					*ast_init(void);
t_redir					*rdir_init(void);
int						is_shovel(char *format, int i);
char					**st_strptrnew(size_t size);
int						is_all_space(char *format, int i);
void					st_init(int *i, int *k, int *hold);
int						skip_char(char *format, int *i, char c);

/* Tokenizer Functions */

int						*tokenize(char **format);
int						arr_length(char **format);
int						is_operator(char *arg);
int						is_command(char *arg);

#endif
