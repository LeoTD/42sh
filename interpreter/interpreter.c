#include "ft_sh.h"

#define RVAL_INITIAL -1
#define CTYPE_INITIAL CMD + 1

t_ast	*fake_ast();

extern char		*g_cmd_symbols[CMD + 1];

char			*g_cmd_symbols[] = {
	[SEP] = ";",
	[AND] = "&&",
	[OR] = "||",
	[NEGATE] = "!",
	[PIPE] = "|",
	[CMD] = NULL
};

extern char		*g_cmd_names[CMD + 1];

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

int	main(void)
{
	puts("hi");
	t_ast *ast = ast_node();
	char *tmp[] = { "a", "na", NULL };
	ast->tokens = tmp;
	print_tokens(ast->tokens);
	puts("");
	t_ast *fake = fake_ast();
	print_tokens(fake->rchild->lchild->tokens);
	return (0);
}
