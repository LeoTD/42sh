#include "ft_sh.h"
#include <sys/param.h>

char		*g_builtin_str[NUM_HANDLED_BUILTINS] = {
	[BIN_CD] = "cd",
	[BIN_ENV] = "env",
	[BIN_ECHO] = "echo",
	[BIN_SETENV] = "setenv",
	[BIN_UNSETENV] = "unsetenv",
};

t_builtin	*g_builtins_dispatch[NUM_HANDLED_BUILTINS] = {
	[BIN_CD] = builtin_cd,
	[BIN_ENV] = builtin_env,
	[BIN_ECHO] = builtin_echo,
	[BIN_SETENV] = builtin_setenv,
	[BIN_UNSETENV] = builtin_unsetenv,
};

/*
** todo: in echo, handle write() failure when blocked
** When using non-blocking I/O on objects, such as sockets, that are subject
** to flow control, write() and writev() may write fewer bytes than requested;
** the return value must be noted, and the remainder of the operation should
** be retried when possible.
*/

/*
** todo: handle echo -n flag
*/

void		builtin_echo(char **args)
{
	int fd;

	fd = dup(1);
	while (*args)
	{
		ft_putstr_fd(*args, fd);
		if (args[1])
			ft_putchar_fd(' ', fd);
		++args;
	}
	ft_putchar_fd('\n', fd);
	exit(0);
}

void		builtin_cd(char **args)
{
	char	*dest;
	char	*cwd;

	cwd = getcwd(NULL, MAXPATHLEN);
	if (args[0] == NULL)
		dest = ft_get_env("HOME", g_environ);
	else if (!ft_strcmp(args[0], "-"))
		dest = ft_get_env("OLDPWD", g_environ);
	else
		dest = args[0];
	if (chdir(dest) != 0)
		perror("42sh");
	else
	{
		ft_set_env("OLDPWD", cwd, g_environ);
		ft_set_env("PWD", getcwd(NULL, MAXPATHLEN), g_environ);
	}
}
