/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 23:31:00 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/16 15:24:08 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"

static int		get_rpos(t_prompt *p)
{
	int			i;
	int			rpos;

	rpos = 1;
	rpos += (p->plen + p->oldpos) / p->cols;
	i = -1;
	while (p->pstr[++i])
		if (p->pstr[i] == '\n')
			rpos++;
	i = -1;
	while (p->buf[++i] && i < (int)p->pos)
		if (p->buf[i] == '\n')
			rpos++;
	return (rpos);
}

static int		get_cpos(t_prompt *p)
{
	int			i;
	int			cpos;

	cpos = p->plen;
	i = -1;
/*	while (p->pstr[++i])
	{
		if (p->pstr[i] == '\n')
			cpos = -1;
	}*/
	i = -1;
	while (p->buf[++i] && i < (int)p->pos)
	{
		cpos++;
		if (p->buf[i] == '\n')
			cpos = 0;
	}
	cpos = cpos % p->cols;
	return (cpos);
}

static int		get_rows(t_prompt *p)
{
	int			i;
	int			rows;

	rows = (p->plen + p->len + p->cols - 1) / p->cols;
	i = -1;
	while (p->pstr[++i])
		if (p->pstr[i] == '\n')
			rows++;
	i = -1;
	while (p->buf[++i])
		if (p->buf[i] == '\n')
			rows++;
	return (rows);
}

/*
** A = up, B = down, C = forward, D = back
** E = next line, F = prev line
*/

int				append_cursor_move(char **dst, int n, char *c)
{
	char		esc[64];
	int			numlen;
	char		*num;

	MALL_CHECK(num = ft_itoa(n));
	numlen = ft_strlen(num);
	ft_strncpy(esc, "\033[", 64);
	ft_strncpy(esc + 2, num, numlen + 1);
	ft_strncpy(esc + 2 + numlen, c, 2);
	free(num);
	ERR_CHECK(append_substr(dst, esc, numlen + 3));
	return (0);
}

int				print_multiline(t_prompt *p)
{
	char		esc[64];
	char		*line;
	int			rows;
	int			rpos;
	int			cpos;

	ft_bzero(esc, 64);
	line = ft_strnew(0);
	p->cols = get_cols();
	rows = get_rows(p);
	if ((int)p->maxrows < rows)
		p->maxrows = rows;
	rpos = get_rpos(p);
	cpos = get_cpos(p);



	ERR_CHECK(append_substr(&line, "\r", 1));
	if (p->maxrows - rpos > 0)
	{
		ERR_CHECK(append_cursor_move(&line, p->maxrows - rpos, "B"));
	}
	if (p->maxrows > 1)
	{
		ERR_CHECK(append_cursor_move(&line, p->maxrows - 1, "A"));
	}

	ERR_CHECK(append_substr(&line, DEL_TERM_SEQ, 4));
	ERR_CHECK(append_substr(&line, p->pstr, p->plen));
	ERR_CHECK(append_substr(&line, p->buf, p->len));
	ERR_CHECK(append_substr(&line, DEL_END_SEQ, 4));

	if (rows - rpos > 0)
	{
		ERR_CHECK(append_cursor_move(&line, rows - rpos, "A"));
	}
	ERR_CHECK(append_substr(&line, "\r", 1));
	if (cpos > 0)
	{
		ERR_CHECK(append_cursor_move(&line, cpos, "C"));
	}
	write(p->ofd, line, ft_strlen(line));

	free(line);
	return (0);
}
