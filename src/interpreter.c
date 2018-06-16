#include "ft_sh.h"
#include "ast.h"

/* TODO: Handle builtins (see builtin_util.c)
** TODO: Don't check PATH if there's a forward slash -- see man 2 execve
** TODO: Print a message when file not found or not executable
*/

int		await_exit_status(pid_t pid, int fd[2], t_ast *a)
{
	int status;

	status = 0;
	if (pid == 0)
	{
		if (a->type == CMD)
			env_exec(a);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		env_exec(a->lchild);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (waitpid(pid, &status, 0) != pid)
			status = -1;
		if (a->type != CMD)
			return (encounter_pipe(a->rchild));
	}
	return (status);
}

int		encounter_pipe(t_ast *a)
{
	pid_t		pid;
	int			fd[2];

	if (a->type == NEGATE)
		return (encounter_pipe(a->rchild));
	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		fprintf(stderr, "Fork error\n");
		_exit(1);
	}
	return (await_exit_status(pid, fd, a));
}

int		ok_next_list(t_ast *a, int exit_status)
{
	int		ok;

	if (a->type == SEP)
		return (1);
	ok = a->type == OR ? exit_status != 0 : exit_status == 0;
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
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		fprintf(stderr, "Fork error\n");
		_exit(1);
	}
	else if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		encounter_new_list(tree, NULL);
	}
	else
		waitpid(pid, NULL, 0);
}
