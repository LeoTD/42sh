/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 22:13:03 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/09 05:54:27 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"

void		reset_term(t_term *t)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &t->normal);
//	_term_do("ve");
}

char		*ft_prompt(char *prompt_str)
{
	t_prompt	p_state;
	t_term		term;

	if (!isatty(STDIN_FILENO))
		return (0);
	term_init(&term);
	if (prompt_init(&p_state, prompt_str) == -1)
	{
		reset_term(&term);
		return (0);
	}
	if (line_edit_loop(&p_state) == -1)
	{
		reset_term(&term);
		return (0);
	}
	ft_putstr_fd("\r\n", p_state.ofd);
	free(p_state.pstr);
	reset_term(&term);
	return (p_state.buf);
}
