#include "ft_sh.h"
#include "ast.h"

/*
** Interpreting the AST form of a parsed command.
** A command list begins with a &&, a || or a semicolon and owns a
** a pipeline -- simple command[s], separated by pipes if plural.
** A list waits for its pipeline to exit, marks its exit status, and
** calls the next list. The next list either executes its pipeline
** or skips itself, depending on the 'ok' flag of the list that called it.
*/

/*
** In `echo hello | ./fail-if-hello && echo hooray || echo :(`...
**
** The && calls its left child, which exits falsy. && sets its 'ok' flag
** to 0. The || cannot run its left child, 'echo hooray'. It sets its
** ok flag to 1 (failure + OR == success). ||'s right child is a pipeline,
** not a list. It sees the ok==1 and just runs itself.
*/

/*
** Pipelines are also trees.
** In `echo hello | tr e x | sed s/hxllo//`,
** the first | has 'echo hello' as its left child and the other pipeline
** as its right child. There is no conditional logic in a pipeline -- if
** it's called, it just runs.
*/

/*
** Negations like `! echo hello | ./fail-if-hello && echo hooray` (note '!')
** are handled by inserting a useless 'pipe-like' node which exists only so that
** the controlling command list, &&, can find out that it was actually negated.
*/

void	interpret_simple_cmd(t_ast *a)
{

/*
** TODO: Handle builtins (see builtin_util.c)
*/

	//fputs("interpret simple command", stderr);
	handle_redirs(a);
	execvp(a->tokens[0], a->tokens);
	_exit(1);
}

/*
** If a->type == CMD, run a:
** -- After forking, so we don't completely lose the controlling process.
** -- Before we would otherwise close/dup, so a's output isn't lost.
*/

int		encounter_pipe(t_ast *a)
{
	pid_t		pid;
	int			status;
	int			fd[2];

	//fputs("encounter pipe", stderr);
	if (a->type == NEGATE)
		return (encounter_pipe(a->rchild));
	status = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (a->type == CMD)
			interpret_simple_cmd(a);
		close(fd[0]);
		close(STDOUT_FILENO);
		dup(fd[1]);
		close(fd[1]);
		interpret_simple_cmd(a->lchild);
	}
	else if (pid == -1)
	{
		fprintf(stderr, "Fork error\n");
		_exit(1);
	}
	else
	{
		close(fd[1]);
		close(STDIN_FILENO);
		dup(fd[0]);
		close(fd[0]);
		if (a->type != CMD)
			encounter_pipe(a->rchild);
		if (waitpid(pid, &status, 0) != pid)
			status = -1;
	}
	return (status);
}

int		ok_next_list(t_ast *a, int exit_status)
{
	int		ok;

	if (a->type == SEP)
		return (1);
	if (a->type == OR)
		ok = (exit_status != 0);
	else
		ok = (exit_status == 0);
	if (a->lchild->type == NEGATE)
		ok = !ok;
	return (ok);
}

/*
** LIST_PRECEDENCE == min of: AND, OR, SEP. See ast.h
** This check is necessary because we currently start out assuming the first
** thing we see is some type of LIST_PRECEDENCE node, but in short
** pipelines, or at the end of any pipeline / list, that won't be true.
*/

void	encounter_new_list(t_ast *a, t_ast *prev)
{
	int		status;
	int		ok;
	//fputs("encounter new list", stderr);

	if (!a)
		return ;
	ok = !prev || prev->ok;
	if (!ok && a->type < LIST_PRECEDENCE)
		return ;
	else if (!ok)
	{
		a->ok = a->type != prev->type;
		encounter_new_list(a->rchild, a);
	}
	else if (a->type < LIST_PRECEDENCE)
	{
		encounter_pipe(a);
	}
	else
	{
		status = encounter_pipe(a->lchild);
		a->ok = ok_next_list(a, status);
		encounter_new_list(a->rchild, a);
	}
}

void	interpret_tree(t_ast *tree)
{
	if (!fork())
		encounter_new_list(tree, NULL);
	else
		wait(0);
}
