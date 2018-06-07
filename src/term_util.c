/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:55:51 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/05 23:25:48 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				ft_weirdchar(int c)
{
	write(TERM_FD, &c, 1);
	return (0);
}

void			update_size(t_term *t)
{
	struct winsize		w;

	ioctl(0, TIOCGWINSZ, &w);
    t->height = w.ws_row;
    t->width = w.ws_col;
}

void			restore_defaults(t_term *t)
{
	tcsetattr(TERM_FD, TCSANOW, &t->normal);
	_term_do("ve");
	_term_do("te");
}
