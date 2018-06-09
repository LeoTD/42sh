/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 22:13:03 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/09 07:53:54 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"

static t_term	g_term;
static int		exit_ready = 0;

void		reset_term(t_term *t)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t->normal);
//	_term_do("ve");
}

void		ft_prompt_cleanup(void)
{
//	reset_term(&g_term);
	cleanup_history();
}

char		*ft_prompt(char *prompt_str)
{
	t_prompt	p_state;

	if (!isatty(STDIN_FILENO))
		return (0);
	term_init(&g_term);
	if (prompt_init(&p_state, prompt_str) == -1)
	{
		reset_term(&g_term);
		return (0);
	}
	if (!exit_ready)
	{
		atexit(ft_prompt_cleanup);
		exit_ready = 1;
	}
	if (line_edit_loop(&p_state) == -1)
	{
		reset_term(&g_term);
		return (0);
	}
	ft_putstr_fd("\r\n", p_state.ofd);
	free(p_state.pstr);
	reset_term(&g_term);
	return (p_state.buf);
}
