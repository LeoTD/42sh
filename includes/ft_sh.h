/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 12:23:11 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/06 21:15:43 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define TERM_FD g_shell->term_fd

/*
** Colors and Formatting!
*/

# define SRC_COLOR	"\033[38;5;105;1m"
# define OBJ_COLOR	"\033[38;5;208m"
# define DIR_COLOR	"\033[38;5;200m"
# define LIB_COLOR	"\033[1;32m"
# define NO_COLOR	"\033[m"
# define UNDERLINE	"\033[4m"
# define SELECTED	"\033[7m"

# define COLUMN_PADDING 4
# define MAX_COLUMN_WIDTH 30

/*
** Function-y macros
*/

# define _term_do(x) tputs(tgetstr(x, NULL), 1, ft_weirdchar)
# define _goto(x, y) tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_weirdchar)
# define _put(x) ft_putstr_fd(x, TERM_FD)

/*
** Input keys
*/

# define ESC_KEY 27
# define UP_KEY 4283163
# define DOWN_KEY 4348699
# define LEFT_KEY 4479771
# define RIGHT_KEY 4414235
# define RETURN_KEY 10
# define SPACE_KEY 32
# define DELETE_KEY 2117294875
# define BACKSPACE_KEY 127

/*
** Structs
*/

typedef struct					s_arg
{
	char				is_sel;
	char				is_hov;
	char				*name;
	struct s_arg		*next;
	struct s_arg		*prev;
}								t_arg;

typedef struct					s_term
{
	char				*name;
	struct termios		normal;
	struct termios		custom;
	int					fd;
	int					height;
	int					width;
	t_arg				*arg_head;
	t_arg				*active;
	int					max_arg_len;
	int					arg_num;
	int					col_w;
	int					col_num;
}								t_term;

typedef struct					s_shell
{
	int					term_fd;
	t_term				term;
	char				*prompt_string;
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
** Global pointer for signal handling
*/

t_shell					g_shellinit;
t_shell					*g_shell;

/*
** Function declarations:
*/

int						ft_weirdchar(int c);
void					update_size(t_term *t);
void					reset_defaults(t_term *t);

void					shell_init(void);
void					prompt(t_shell *s);
void					term_init(t_term *t);

/*
**  Parser functions:
*/

t_proc					*process_init(void);
t_job					*job_init(void);
char					**split_args(char *format);

#endif
