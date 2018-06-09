#include "ft_sh.h"
#include "ast.h"

t_ast	*fake_ast();

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

void	interpret_command(t_ast *a)
{
	fprintf(stderr, "interpret command: "); print_node(a);
	execvp(a->tokens[0], a->tokens);
	_exit(1);
}

int		interpret_pipe(t_ast *a)
{
	pid_t		pid;
	int			status;
	int			fd[2];

	fprintf(stderr, "interpret pipe: <"); print_node(a); fprintf(stderr, ">\n");
	if (a->type == NEGATE)
		return (!(interpret_pipe(a->lchild)));
	if (a->type == CMD)
		interpret_command(a);
	status = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		close(STDOUT_FILENO);
		dup(fd[1]);
		close(fd[1]);
		interpret_command(a->lchild);
	}
	else
	{
		close(fd[1]);
		close(STDIN_FILENO);
		dup(fd[0]);
		close(fd[0]);
		interpret_pipe(a->rchild);
		if (waitpid(pid, &status, 0) != pid)
			status = -1;
	}
	return (status);
}

void	interpret_list(t_ast *a, int ok_to_execute)
{
	if (a->type < LIST_PRECEDENCE)
	{
		interpret_pipe(a);
		return ;
	}
	if (ok_to_execute)
		ok_to_execute = interpret_pipe(a->lchild);
	ok_to_execute = (ok_to_execute && a->type != AND)
		|| (!ok_to_execute && a->type == OR)
		|| a->type == SEP;
	interpret_list(a->rchild, ok_to_execute);
}

int	main(void)
{
	t_ast *a = fake_ast();
	interpret_pipe(a);
	a = fake_ast();
	interpret_pipe(a);
	return (0);
}
