/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 00:54:00 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/09 06:46:26 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"

int				extend_buf(t_prompt *p)
{
	char		*tmp;

	p->buf_size *= 2;
	MALL_CHECK(tmp = ft_strnew(p->buf_size));
	ft_memcpy(tmp, p->buf, p->len);
	free(p->buf);
	p->buf = tmp;
	return (0);
}

int				edit_insert(t_prompt *p, long c)
{
	if (p->len == p->buf_size)
		if (extend_buf(p) == -1)
			return (-1);
	if (p->pos == p->len)
	{
		p->buf[p->pos] = (char)c;
		p->pos++;
		p->len++;
		p->buf[p->len] = '\0';
	}
	else
	{
		ft_memmove(p->buf + p->pos + 1, p->buf + p->pos, p->len - p->pos);
		p->buf[p->pos] = (char)c;
		p->pos++;
		p->len++;
		p->buf[p->len] = '\0';
	}
	print_line(p);
	return (0);
}

int				line_edit_loop(t_prompt *p, int status, long c)
{
	ft_prompt_history_add("");
	print_line(p);
	while (!status)
	{
		c = 0;
		read(p->ifd, &c, 8);
		if (c == ESC)
			;
		else if (c == CTRL_K)
			status = copy_line(p);
		else if (c == CTRL_P)
			status = paste_line(p);
		else if (c == UP_ARR || c == DOWN_ARR)
			status = move_through_history(p, (c == UP_ARR ? 1 : -1));
		else if (c == LEFT_ARR || c == RIGHT_ARR || c == CTRL_A || c == CTRL_E)
			status = cursor_move(p, c);
		else if (c == DELETE || c == BACKSPACE)
			status = edit_delete(p, c);
		else if (c >= 32 && c <= 126)
			status = edit_insert(p, c);
		else if (c == ENTER)
			return (forget_most_recent());
	}
	return (status);
}
