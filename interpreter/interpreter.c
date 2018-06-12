#include "ft_sh.h"
#include "ast.h"
#include "_interpreter_dev.h"

void	interpret_cmd(t_ast *a)
{
	execvp(a->tokens[0], a->tokens);
	_exit(1);
}

int		interpret_pipe(t_ast *a)
{
	pid_t		pid;
	int			status;
	int			fd[2];

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
	run_interpreter_tests();
	return (0);
}
