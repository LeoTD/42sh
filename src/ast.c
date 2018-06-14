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

t_ast	*ast_node(void)
{
	t_ast	*a;

	a = ft_memalloc(sizeof(*a));
	a->ok = 1;
	return (a);
}

t_ast	*opnode(t_cmdtype type)
{
	t_ast	*a;

	a = ast_node();
	a->type = type;
	return (a);
}

t_ast	*cmd_node(char **tokens)
{
	t_ast	*a;

	a = ast_node();
	a->type = CMD;
	a->tokens = tokens;
	return (a);
}

char	**fetch_tokens(char **args, int hp)
{
	char	**ptr;
	int		i;

	i = 0;
	if ((ptr = (char **)malloc(sizeof(char *) * (arr_length(args+hp) + 1))))
		return (NULL);
	while (*(args + hp))
		ptr[i++] = ft_strdup(*(args + hp++));
	ptr[i] = NULL;
	int x = 0;
	while (ptr[x++])
	  printf("%s\n", ptr[x]);
	return (ptr);
}

t_ast	*parsed_ast_node(char **args, int *cmdtypes, int hp)
{
	t_ast *a;

	a = ft_memalloc(sizeof(*a));
	a->tokens = fetch_tokens(args, hp);
	a->type = cmdtypes[hp];
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

int		highest_prec(int *cmdtypes)
{
	int i;

	i = -1;
	while (cmdtypes[++i])
		if (cmdtypes[i] >= OR && cmdtypes[i] <= SEP)
			return (i);
	i = -1;
	while (cmdtypes[++i])
		if (cmdtypes[i] == PIPE || cmdtypes[i] == NEGATE)
			return (i);
	return (0);
}

void	print_tree(t_ast *ast, int i)
{
	if (ast)
	{
		fprintf(stderr, "[lvl %d]: node type %s, tokens: ", i,
			   g_nodetype_names[ast->type] ? g_nodetype_names[ast->type] : "CMD");

		fputs("here\n", stderr);
			fprintf(stderr, "%s, ", ast->tokens[0]);
		for (int j = 0; ast->tokens[j]; j++)
			fprintf(stderr, "%s, ", ast->tokens[j]);
		fputs("\n", stderr);
		i += 1;
		if (ast->lchild)
		{
			print_tree(ast->lchild, i);
		}
		if (ast->rchild)
		{
			print_tree(ast->rchild, i);
			ft_putendl("");
		}
	}
}

void	create_tree(char **args, int *cmdtypes, t_ast **head, int hp)
{
	t_ast *ast;

	if (hp != 0)
	{
		*head = parsed_ast_node(args, cmdtypes, hp);
		ast = *head;
		cmdtypes[hp] = 0;
		if (args+hp)
			create_tree(args, cmdtypes, &(ast->lchild), highest_prec(cmdtypes));
		else if (args+hp)
			create_tree(args+(hp + 1), cmdtypes+(hp + 1), &(ast->rchild), highest_prec(cmdtypes + (hp + 1)));
	}
	else
		*head = parsed_ast_node(args, cmdtypes, hp);
	print_tree(*head, 1);
//	printf("%s \n%s \n%s\n", head->tokens[0], head->lchild->tokens[0], head->rchild->tokens[0]);
//	return (head);
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
