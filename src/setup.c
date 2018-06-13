/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:40:14 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/12 20:43:27 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		term_init(t_term *t)
{
	t->name = getenv("TERM");
	t->fd = open("/dev/tty", O_RDWR);
	tgetent(0, t->name);
	tcgetattr(TERM_FD, &t->normal);
	tcgetattr(TERM_FD, &t->custom);
	t->custom.c_lflag |= ICANON;
	t->custom.c_lflag |= ECHOE;
	t->custom.c_lflag |= ECHOK;
	t->custom.c_cc[VMIN] = 1;
	t->custom.c_cc[VTIME] = 0;
	tcsetattr(TERM_FD, TCSANOW, &t->custom);
	_term_do("ti");
	_term_do("vs");
	update_size(t);
}

void		shell_init(void)
{
	g_shell = &g_shellinit;
	term_init(&g_shell->term);
	g_shell->prompt_string = ft_strdup("marvin");

	
}

t_ast		*ast_init(void)
{
	t_ast	*ast;

	if (!(ast = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	ft_bzero(ast->tokens, 1024);
	ast->rval = 0;
	ast->lchild = NULL;
	ast->rchild = NULL;
	return (ast);
}

t_redir		*rdir_init(void)
{
	t_redir	*rdir;

	rdir = (t_redir *)malloc(sizeof(t_redir));
	ft_bzero(rdir, sizeof(t_redir));
	rdir->word = NULL;
	return (rdir);
}
