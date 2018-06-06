/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 22:23:32 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/05 00:51:47 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		prompt(t_shell *s)
{
	char		*buf;
	char		done;

	done = 0;
	while (!done)
	{
		ft_printf("%s$>", s->prompt_string);
		get_next_line(1, &buf);
//		get_func_id
	}
}
