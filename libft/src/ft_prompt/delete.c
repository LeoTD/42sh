/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 04:17:51 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/08 07:51:13 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"

int				edit_delete(t_prompt *p, long c)
{
	if (c == BACKSPACE)
	{
		if (p->pos > 0 && p->len > 0)
		{
			ft_memmove(p->buf + p->pos - 1, p->buf + p->pos, p->len - p->pos);
			p->pos--;
			p->len--;
			p->buf[p->len] = '\0';
		}
	}
	if (c == DELETE)
	{
		if (p->pos != p->len)
		{
			ft_memmove(p->buf + p->pos, p->buf + p->pos + 1, p->len - p->pos);
			p->len--;
			p->buf[p->len] = '\0';
		}
	}
	print_line(p);
	return (0);
}
