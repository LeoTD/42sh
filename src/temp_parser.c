/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 19:55:28 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/05 21:12:33 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

/*
** Temporary parse function. To be replaced by full featured parser.
*/

void			parse_commands(t_shell *s, char *buf)
{
	s->temp_args = ft_strsplit(buf, ' ');
}
