#include "ft_sh.h"

void		shell_init(void)
{
	g_shell = &g_shellinit;
	term_init(&g_shell->term);
}

t_ast		*ast_init(void)
{
	t_ast	*ast;

	if (!(ast = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	ft_bzero(ast->tokens, 1024);
	ast->lchild = NULL;
	ast->rchild = NULL;
	return (ast);
}

t_redir		*rdir_init(void)
{
	t_redir	*rdir;

	rdir = (t_redir *)malloc(sizeof(t_redir));
	ft_bzero(rdir, sizeof(t_redir));
	return (rdir);
}
