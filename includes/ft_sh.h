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

/* A process is a single process.  */

typedef struct					s_proc
{
	struct process		*next;
	char				**argv;
	int					is_pipe;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					status;
}								t_proc;

/* A job is a pipeline of processes.  */

typedef struct					s_job
{
	struct job			*next;
	struct job			*prev;
	struct termios		tmodes;
	int					s_in;
	int					s_out;
	int					s_err;
	t_proc				*first_process;
	char				command;
	char				notified;
	pid_t				pgid;
}								t_job;

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

#define DQUOTE '\"'
#define QUOTE '\''
#define BQUOTE '`'
#define SUBSH '('
#define NEWLINE '\\'
#define DQUOTE_PROMPT "dquote> "
#define QUOTE_PROMPT "quote> "
#define BQUOTE_PROMPT "bquote> "
#define SUBSH_PROMPT "subsh> "
#define NEWLINE_PROMPT "> "

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

char					correct_syntax(char *str);

#endif
