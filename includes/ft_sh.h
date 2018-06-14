#ifndef FT_SH_H
# define FT_SH_H

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
** Declaration of environ.
** Contains environment variables in the form:
** NAME=VAL
*/

extern char						**environ;

/*
** Structs
*/

typedef struct					s_shell
{
	t_term				term;
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

void					update_size(t_term *t);

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


#endif
