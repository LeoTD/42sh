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

t_ast	*ast_node(char **args, int *tokens, int hp)
{
	t_ast *a;

	a = ft_memalloc(sizeof(*a));
	a->tokens = args;
	a->lchild = NULL;
	a->rchild = NULL;
	a->type = hp;
	a->ok = 0;
	a->redirs = NULL;
	tokens = tokens + 1;
	return (a);
}

t_redir	*new_redir(void)
{
	return ((t_redir *)ft_memalloc(sizeof(t_redir)));
}

int		highest_prec(int *tokens, int len)
{
	int i;
	int count;

	i = -1;	
	count = 0;
	while (++i < len)
	{
//		printf("HERE == %d\n", tokens[i]);
		if (tokens[i] >= OR && tokens[i] <= SEP)
			return (tokens[i]);
	}
	if (count > 0)
		return (count);
	i = -1;
	while (++i < len)
		if (tokens[i] >= PIPE)
			return (i);
	return (-1);
}

t_ast	*create_tree(char **args, int *tokens, t_ast *head, int hp)
{
//	printf("%d\n", hp);
	if (!head)
	{
		head = ast_node(args, tokens, hp);
	}
//	if (_op(tokens[i]))
//	{
//		
//	}
	return (head);
}
