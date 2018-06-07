#ifndef FT_SH_H
# define FT_SH_H

# include "libft.h"
# include "ft_printf.h"
# include <termcap.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>

# define TERM_FD g_shell->term.fd

extern char						**environ;

/*
** Function-y macros for terminal and cursor manipulation.
*/

# define _term_do(x) tputs(tgetstr(x, NULL), 1, ft_weirdchar)
# define _goto(x, y) tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_weirdchar)
# define _put(x) ft_putstr_fd(x, TERM_FD)

/*
** Structs
*/

typedef struct					s_term
{
	char				*name;
	struct termios		normal;
	struct termios		custom;
	int					fd;
	int					height;
	int					width;
}								t_term;

typedef struct					s_shell
{
	t_term				term;
	char				*prompt_string;
	char				**temp_args;
}								t_shell;

/*
** Global pointer for signal handling.
** For future development.
*/

t_shell					g_shellinit;
t_shell					*g_shell;

/*
** Function declarations:
*/

int						ft_weirdchar(int c);
void					update_size(t_term *t);
void					restore_defaults(t_term *t);

void					shell_init(void);
void					prompt(t_shell *s);
void					parse_commands(t_shell *s, char *buf);
void					term_init(t_term *t);

/*
** Builtin Function Declarations.
*/

int						run_builtin(int id, char **args);
int						is_builtin(char *str);

int						ftsh_cd(char **args);
int						ftsh_help(char **args);
int						ftsh_exit(char **args);

#endif
