#include "ft_sh.h"

#define RVAL_INITIAL -1
#define CTYPE_INITIAL CMD + 1

t_ast	*fake_ast();

void	print_tokens(char **tokens)
{
	printf("%s", "[");
	int i = 0;
	while (tokens[i])
	{
		printf("%d: '%s'%s", i, tokens[i], tokens[i + 1] ? ", " : "]");
		++i;
	}
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