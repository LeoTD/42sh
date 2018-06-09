/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 22:14:36 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/09 07:28:31 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROMPT_H
# define FT_PROMPT_H

# include "libft.h"
# include "ft_printf.h"
# include <termcap.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define LINE_START_SIZE 256
# define MAX_HISTORY_LEN 200

# define MALL_CHECK(x) if (!(x)) return (-1)
# define ERR_CHECK(x) if ((x) == -1) return (-1)

/* Deletes from the cursor until end of term */
# define DEL_END_SEQ "\033[0K"

/* Reports the cursor position as: "ESC[x;yR" */
# define DSR_SEQ "\033[6n"

/*
** Input keys
*/

enum							e_key_press
{
	KEY_NULL = 0,
	CTRL_A = 1,
	CTRL_B = 2,
	CTRL_C = 3,
	CTRL_D = 4,
	CTRL_E = 5,
	CTRL_F = 6,
	CTRL_H = 8,
	TAB = 9,
	CTRL_K = 11,
	CTRL_L = 12,
	ENTER = 13,
	CTRL_N = 14,
	CTRL_P = 16,
	CTRL_T = 20,
	CTRL_U = 21,
	CTRL_W = 23,
	ESC = 27,
	BACKSPACE =  127,
	DELETE = 2117294875,
	UP_ARR = 4283163,
	DOWN_ARR = 4348699,
	LEFT_ARR = 4479771,
	RIGHT_ARR = 4414235
};

/*
** Structs
*/

typedef struct					s_prompt
{
	int					ifd;
	int					ofd;
	char				*pstr;
	size_t				plen;
	char				*buf;
	size_t				buf_size;
	size_t				len;
	size_t				cols;
	size_t				pos;
	int					his_idx;
}								t_prompt;

typedef struct					s_term
{
	char				*name;
	struct termios		normal;
	struct termios		custom;
	int					fd;
	int					height;
	int					width;
}								t_term;

/*
** Function Declarations
*/

char					*ft_prompt(char *prompt_str);
int						line_edit_loop(t_prompt *p);
int						term_init(t_term *t);
int						prompt_init(t_prompt *p, char *pstr);
int						print_line(t_prompt *p);

/*
** Editing functions
*/

int						edit_insert(t_prompt *p, long c);
int						edit_delete(t_prompt *p, long c);
int						cursor_move(t_prompt *p, long c);

/*
** History functions
*/

int						move_through_history(t_prompt *p, int dir);
int						ft_prompt_history_set_len(int len);
int						ft_prompt_history_add(char *str);

/*
** Cleanup functions
*/

void					ft_prompt_cleanup(void);
int						forget_most_recent(void);
void					cleanup_history(void);
void					reset_term(t_term *t);

#endif
