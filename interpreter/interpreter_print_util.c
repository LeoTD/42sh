#include "ft_sh.h"
#include "ast.h"

void	print_tokens(char **tokens)
{
	if (!tokens)
	{
		fprintf(stderr, "(null)");
		return;
	}
	fprintf(stderr, "%s", "[");
	int i = 0;
	while (tokens[i])
	{
		fprintf(stderr, "'%s'%s", tokens[i], tokens[i + 1] ? ", " : "]");
		++i;
	}
}

void	print_node(t_ast *a)
{
	if (!a)
		fprintf(stderr, "%s", NULL);
	else
		print_tokens(a->tokens);
}

void	print_pipe(int fd[2])
{
	fprintf(stderr, "(%d -> %d)", fd[1], fd[0]);
}

void	examine_tree(t_ast *a)
{
	if (a == NULL)
		return ;
	print_tokens(a->tokens);fprintf(stderr, ": My type is '%s'!", g_cmd_names[a->type]);
	if (a->lchild == NULL && a->rchild == NULL)
		fprintf(stderr, "\n\tNo children. :(\n");
	else
	{
		fprintf(stderr, "\n\tMy left child is "); print_node(a->lchild);
		fprintf(stderr, "\n\tand my right child is "); print_node(a->rchild); fputs(".", stderr);
	}
	examine_tree(a->lchild);
	examine_tree(a->rchild);
}

char	*redir_op_names[] =
{
	[TRUNC] = ">",
	[APPEND] = ">>",
	[INPUT] = "<",
};

void	examine_redir(t_redir *r)
{
	fprintf(stderr, "%d %s %s %s\n",
			r->to_fd, redir_op_names[r->op], r->from_file, r->file_string_represents_fd ? "(fd)" : "");
}
