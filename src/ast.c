#include "ft_sh.h"
#include "ast.h"

char	*g_cmd_symbols[] =
{
	[SEP] = ";",
	[AND] = "&&",
	[OR] = "||",
	[NEGATE] = "!",
	[PIPE] = "|",
	[CMD] = NULL
};

char	*g_cmd_names[] =
{
	[SEP] = "separator",
	[AND] = "and_list",
	[OR] = "or_list",
	[NEGATE] = "negation",
	[PIPE] = "pipe",
	[CMD] = "simple_cmd"
};

t_ast	*ast_node(void)
{
	t_ast *a;

	a = ft_memalloc(sizeof(*a));
	a->ok = 1;
	return (a);
}

t_ast	*opnode(t_cmdtype type)
{
	t_ast *a;

	a = ast_node();
	a->type = type;
	a->tokens = ft_memalloc(sizeof(char *) * 2);
	a->tokens[0] = g_cmd_symbols[type];
	return (a);
}

t_ast	*cmd_node(char **tokens)
{
	t_ast *a;

	a = ast_node();
	a->type = CMD;
	a->tokens = tokens;
	return (a);
}

t_redir	*new_redir(void)
{
	return ((t_redir *)ft_memalloc(sizeof(t_redir)));
}

t_redir			*quick_redir(int to_fd, enum e_redirect op, char *from, int is_fd)
{
	t_redir *r;

	r = new_redir();
	r->to_fd = to_fd;
	r->op = op;
	r->from_file = ft_strdup(from);
	r->file_string_represents_fd = is_fd;
	return (r);
}

void			append_redir(int to_fd, enum e_redirect op,
		char *from, int is_fd, t_ast *a)
{
	t_list	*newredir;
	t_list	*iter;

	newredir = ft_lstnew(quick_redir(to_fd, op, from, is_fd), sizeof(t_redir));
	if (!a->redirs)
		a->redirs = newredir;
	else
	{
		iter = a->redirs;
		while (iter->next)
			iter = iter->next;
		iter->next = newredir;
	}
}
