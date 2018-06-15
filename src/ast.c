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

char	**fetch_tokens(char **args)
{
	char	**ptr;
	int	i;
	
	i = 0;
	if ((ptr = (char **)malloc(sizeof(char *) * arr_length(args))))
		return (NULL);
	while (*(args) && !_op(*(args[0])))
		ptr[i++] = ft_strdup(*(args));
	ptr[i] = NULL;
	return (ptr);
}

t_ast	*parsed_ast_node(char **args, int *tokens, int hp)
{
	t_ast *a;

	a = ft_memalloc(sizeof(*a));
	if (_op((*(args))[0]))
	  {
	    if (!(a->tokens = st_strptrnew(2)))
	      return (NULL);
	    *(a->tokens) = *args;
	    *args = NULL;
	  }
	else
	  a->tokens = args;
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
		if (tokens[i] == PIPE || tokens[i] == NEGATE)
			return (i);
	return (0);
}

void	print_tree(t_ast *ast, int i, int lr)
{
	if (ast)
	{
		if (lr == -1)
			ft_printf("type = %s___ level = %d ___ top\n", *(ast->tokens), i);
		else
			ft_printf("type = %s ___ level = %d ___ left | right = %c\n", *(ast->tokens), i, lr ? 'l' : 'r');
		for (int x = 0; ast->tokens[x]; x++)
			ft_printf("token %d == %s\n", x, ast->tokens[x]);
		ft_putendl("");
		i++;
		if (ast->lchild)
			print_tree(ast->lchild, i, 1);
		if (ast->rchild)
			print_tree(ast->rchild, i, 0);
	}
}

void	create_tree(char **args, int *tokens, t_ast **head, int hp)
{
	t_ast *ast;

	if (*args && (hp != 0 || _op((*args)[0])))
	{
		*head = parsed_ast_node(args+hp, tokens, hp);
		ast = *head;
		tokens[hp] = 0;
		if (args+hp)
			create_tree(args, tokens, &(ast->lchild), highest_prec(tokens));
		if (args+hp)
			create_tree(args+(hp + 1), tokens+(hp + 1), &(ast->rchild), highest_prec(tokens + (hp + 1)));
	}
	else if (*args)
		*head = parsed_ast_node(args, tokens, hp);
}
