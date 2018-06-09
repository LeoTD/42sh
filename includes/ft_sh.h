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

/*
** POSIX standard redirect types. We don't (yet?) handle all of them.
** pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_07
**	in	out	noclobber	append	heredoc		in_dup	out_dup	rdwr
**	<	>	|>			>>		<< or <<-	&<		&>		<>
*/

typedef enum					e_redir_op
{
	INPUT,
	OUTPUT,
	OUTPUT_NOCLOBBLER,
	OUTPUT_APPEND,
	HEREDOC,
	INPUT_DUP,
	OUTPUT_DUP,
	RDWR
}								t_redir_op;

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
** Input functions.
*/

char					*ft_prompt(char *prompt_str);

/*
**  Parser functions:
*/

t_proc					*process_init(void);
t_job					*job_init(void);
char					**split_args(char *format);

/*
** Builtin Function Declarations.
*/

int						run_builtin(int id, char **args);
int						is_builtin(char *str);

int						ftsh_cd(char **args);
int						ftsh_help(char **args);
int						ftsh_exit(char **args);

/*
** PARSE_LINE.c
*/

char					*ft_strjoin_newline(char const *s1, char const *s2);
char					*concatinated_string(char type);
char					*get_type_prompt(char value);
void					cont_chars_capsules(char *str, char schar, int *cont);
char					is_capsule_incomplete(char *str, char **temp);
char					*parse_line(char *str);


#endif
