/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 03:47:08 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/09 08:16:36 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"

static char		**g_history = NULL;
static int		g_history_max_len = 1;
static int		g_history_len = 0;

/*
** [ dir ] should be [  1 ] to go to next
** 					 [ -1 ] to go to prev
*/

int				move_through_history(t_prompt *p, int dir)
{
	if (g_history_len == 1)
		return (0);
	free(g_history[p->his_idx]);
	MALL_CHECK(g_history[p->his_idx] = ft_strdup(p->buf));
	p->his_idx += dir;
	if (p->his_idx < 0)
		return (p->his_idx = 0);
	if (p->his_idx == g_history_len)
	{
		p->his_idx = g_history_len - 1;
		return (0);
	}
	ft_strncpy(p->buf, g_history[p->his_idx], LINE_START_SIZE);
	p->buf[p->buf_size - 1] = '\0';
	p->len = ft_strlen(p->buf);
	p->pos = p->len;
	return (print_line(p));
}

/*
** Public API calls return [ 1 ] on success
** 						   [ 0 ] on failure
*/

int				ft_prompt_history_add(char *str)
{
	char		*tmp;

	if (g_history_max_len == 0)
		return (0);
	if (g_history == NULL)
	{
		if (!(g_history = malloc(sizeof(char *) * g_history_max_len)))
			return (0);
		ft_bzero(g_history, (sizeof(char *) * g_history_max_len));
	}
	if (g_history_len && !ft_strcmp(g_history[0], str))
		return (0);
	if (!(tmp = ft_strdup(str)))
		return (0);
	if (g_history_len == g_history_max_len)
		free(g_history[--g_history_len]);
	ft_memmove(g_history + 1, g_history,
			sizeof(char *) * (g_history_max_len - 1));
	g_history[0] = tmp;
	g_history_len++;
	return (1);
}

int				ft_prompt_history_set_len(int len)
{
	if (len < 2 || g_history_max_len > 1)
		return (0);
	g_history_max_len = len;
	return (1);
}

int				forget_most_recent(void)
{
	free(g_history[0]);
	ft_memmove(g_history, g_history + 1,
			sizeof(char *) * (g_history_max_len - 1));
	g_history_len--;
	return (0);
}

void			cleanup_history(void)
{
	int			i;

	if (g_history == NULL)
		return ;
	i = -1;
	while (++i < g_history_len)
		free(g_history[i]);
	free(g_history);
}
