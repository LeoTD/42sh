/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 20:00:22 by jgelbard          #+#    #+#             */
/*   Updated: 2018/06/28 21:20:56 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"

/*
 **	Signal is sent to copy the line. Take the current line that is inside
 **	ft_prompt, and store it into a temporary buffer.
 **	If a temporary buffer exists, free and clear the old one and realloc
 **	a new space for it.
 **	
 */

int		copy_line(t_prompt *p)
{
	ft_strclr(p->clipboard);
	free(p->clipboard);
	if (!(p->clipboard = ft_strdup(p->buf)))
		return (1);
	return (0);
}

/*
 **	Signal is sent to paste the line. Take the current prompt and 
 **	concatenate with the clipboard. If the clipboard is empty, do nothing.
 **	Call edit insert for the length of the string to be concatentated.
 */

int		paste_line(t_prompt *p)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(p->clipboard))
	{
		edit_insert(p, p->clipboard[i]);
		++i;
	}
	return (0);
}
