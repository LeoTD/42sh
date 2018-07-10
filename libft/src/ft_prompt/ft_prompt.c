/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 22:13:03 by ltanenba          #+#    #+#             */
/*   Updated: 2018/07/10 14:34:03 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"

static t_term	g_term;
static t_prompt	g_state;

char		*reset_term(t_term *t)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t->normal);
	return (0);
}

void		ft_prompt_cleanup(void)
{
	free(g_state.clipboard);
	cleanup_history();
}

char		*ft_prompt(char *prompt_str)
{
	static int	exit_ready = 0;

	if (!isatty(STDIN_FILENO))
		return (0);
	term_init(&g_term);
	if (prompt_init(&g_state, prompt_str) == -1)
		return (reset_term(&g_term));
	if (!exit_ready)
	{
		atexit(ft_prompt_cleanup);
		exit_ready = 1;
	}
	if (line_edit_loop(&g_state, 0, 0) == -1)
		return (reset_term(&g_term));
	ft_putstr_fd("\r\n", g_state.ofd);
	free(g_state.pstr);
	reset_term(&g_term);
	return (g_state.buf);
}
