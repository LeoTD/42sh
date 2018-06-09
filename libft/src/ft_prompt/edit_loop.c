/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 00:54:00 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/08 08:27:51 by ltanenba         ###   ########.fr       */
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

int				line_edit_loop(t_prompt *p)
{
	long		c;
	int			status;

	status = 0;
	print_line(p);
	while (!status)
	{
		c = 0;
		read(p->ifd, &c, 8);
//		printf("%ld\n\r", c);
		if (c == ESC)
			;//Escape Sequences!
		else if (c == UP_ARR || c == DOWN_ARR)
			status = cursor_move(p, c);//TODO: Handle history. Temp: Home/End
		else if (c == LEFT_ARR || c == RIGHT_ARR)
			status = cursor_move(p, c);//Handle cursor movement
		else if (c == DELETE || c == BACKSPACE)
			status = edit_delete(p, c);//Handle deletion
		else if (c >= 32 && c <= 126)
			status = edit_insert(p, c);//Add ("type") to buffer.
		else if (c == ENTER)
			return (0);//Send command
	}
	return (status);
}
