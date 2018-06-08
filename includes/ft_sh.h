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

/*
** Possible types for AST nodes.
** sep		and		or		negate	pipe	cmd
** ;		&&		||		!		|		simple command, eg ">2 cat <file"
*/

typedef enum					e_cmdtype
{
	SEP,
	AND,
	OR,
	NEGATE,
	PIPE,
	CMD
}								t_cmdtype;

/*
** Redirects take the form `[n]redir-op word', where `n' is an (optional) file
** descriptor and `word' (required) can be either a file path or a file
** descriptor. POSIX standard requires support for FDs 0..9 at minimum.
*/

typedef struct					s_redir
{
	t_redir_op			op;
	int					fd;
	char				*word;
}								t_redir;

typedef struct					s_ast
{

	char				**tokens;
	t_redir				redir[10];
	struct s_ast		*lchild;
	struct s_ast		*rchild;
	int					rval;
	t_cmdtype			ctype;
}								t_ast;

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

int						ft_weirdchar(int c);
void					update_size(t_term *t);
void					restore_defaults(t_term *t);

void					shell_init(void);
void					prompt(t_shell *s);
void					parse_commands(t_shell *s, char *buf);
void					term_init(t_term *t);

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

#endif
