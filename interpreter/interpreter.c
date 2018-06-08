#include "ft_sh.h"

#define RVAL_INITIAL -1
#define CTYPE_INITIAL CMD + 1

t_ast	*fake_ast();

extern char		*g_cmd_symbols[MAX_CMDTYPE + 1];

char			*g_cmd_symbols[] = {
	[SEP] = ";",
	[AND] = "&&",
	[OR] = "||",
	[NEGATE] = "!",
	[PIPE] = "|",
	[CMD] = NULL
};

extern char		*g_cmd_names[MAX_CMDTYPE + 1];

char			*g_cmd_names[] = {
	[SEP] = "separator",
	[AND] = "and_list",
	[OR] = "or_list",
	[NEGATE] = "negation",
	[PIPE] = "pipe",
	[CMD] = "simple_cmd"
};

void	print_tokens(char **tokens)
{
	if (!tokens)
	{
		printf("(null)");
		return;
	}
	printf("%s", "[");
	int i = 0;
	while (tokens[i])
	{
		printf("'%s'%s", tokens[i], tokens[i + 1] ? ", " : "]");
		++i;
	}
}

void	print_node(t_ast *a)
{
	if (!a)
		printf("%s", NULL);
	else
		print_tokens(a->tokens);
}

t_ast	*ast_node()
{
	t_ast *ast = ft_memalloc(sizeof(*ast));
	ast->rval = RVAL_INITIAL;
	ast->ctype = CTYPE_INITIAL;
	return (ast);
}

void	examine_tree(t_ast *a)
{
	if (a == NULL)
		return ;
	print_tokens(a->tokens);printf(": My type is '%s'!", g_cmd_names[a->ctype]);
	if (a->lchild == NULL && a->rchild == NULL)
		printf("\n\tNo children. :(\n");
	else
	{
		printf("\n\tMy left child is "); print_node(a->lchild);
		printf("\n\tand my right child is "); print_node(a->rchild); puts(".");
	}
	examine_tree(a->lchild);
	examine_tree(a->rchild);
}

int	main(void)
{
	return (0);
}
