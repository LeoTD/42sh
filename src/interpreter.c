#include "ft_sh.h"
#include "ast.h"

void	interpret_simple_cmd(t_ast *a)
{

/* TODO: Handle builtins (see builtin_util.c)
** TODO: Don't check PATH if there's a forward slash -- see man 2 execve
** TODO: Print a message when file not found or not executable
*/

	handle_redirs(a);
	if (access(a->tokens[0], X_OK) != -1)
		execve(a->tokens[0], a->tokens, environ);
	else
		env_exec(a);
	_exit(1);
}

int		encounter_pipe(t_ast *a)
{
	pid_t		pid;
	int			status;
	int			fd[2];

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

void	encounter_new_list(t_ast *a, t_ast *prev)
{
	int		status;
	int		ok;

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
