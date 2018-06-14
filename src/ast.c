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

t_ast	*parsed_ast_node(char **args, int *tokens, int hp)
{
	t_ast *a;

	a = ft_memalloc(sizeof(*a));
	a->tokens = args + hp;
	a->type = tokens[hp];
	a->ok = 0;
	a->lchild = NULL;
	a->rchild = NULL;
	a->redirs = NULL;
	return (a);
}

t_redir	*new_redir(void)
{
	return ((t_redir *)ft_memalloc(sizeof(t_redir)));
}

int		highest_prec(int *tokens)
{
	int i;

	i = -1;	
	while (tokens[++i])
		if (tokens[i] >= OR && tokens[i] <= SEP)
			return (i);
	i = -1;
	while (tokens[++i])
		if (tokens[i] == PIPE)
			return (i);
	return (0);
}

void	print_tree(t_ast *ast, int i)
{
	if (ast)
	{
		printf("type = %s level %d\n", *(ast->tokens), i);
		i += 1;
		if (ast->lchild)
		{
			print_tree(ast->lchild, i);
		}
		if (ast->rchild)
		{
			print_tree(ast->rchild, i);
		}
	}
}

void	create_tree(char **args, int *tokens, t_ast **head, int hp)
{
	t_ast *ast;

	if (hp != 0)
	{
		*head = parsed_ast_node(args, tokens, hp);
		ast = *head;
		tokens[hp] = 0;
		if (args+hp)
			create_tree(args, tokens, &(ast->lchild), highest_prec(tokens));
		if (args+hp)
			create_tree(args+(hp + 1), tokens+(hp + 1), &(ast->rchild), highest_prec(tokens + (hp + 1)));
	}
	else
		*head = parsed_ast_node(args, tokens, hp);
//	print_tree(head);
//	printf("%s \n%s \n%s\n", head->tokens[0], head->lchild->tokens[0], head->rchild->tokens[0]);
//	return (head);
}
