#include "ft_sh.h"

int			ftsh_cd(char **args)
{
	if (args[1] == NULL)
		ft_putstr_fd("expected argument to \"cd\"\n", STDERR_FILENO);
	else
	{
		if (chdir(args[1]) != 0)
			perror("42sh");
	}
	return (1);
}

int			ftsh_help(char **args)
{
	ft_putendl("This is 42sh!");
	ft_putendl(" - - - - - - ");
	args = 0;
	return (1);
}

int			ftsh_exit(char **args)
{
	args = 0;
	return (0);
}

int			ftsh_echo(char **args)
{
	int			i;

	i = 0;
	while (args[++i] != NULL)
	{
		if (i > 1)
			ft_putchar(' ');
		ft_putstr(args[i]);
	}
	return (0);
}

/*
** Usage:
** setenv VAR [VALUE]
*/

/*
int			ftsh_setenv(char **args)
{
	int			i;
	int			nlen;

	if (args[1] == NULL)
		return (ftsh_env(args));
	nlen = (int)ft_strlen(args[1]);
	i = -1;
	while (environ[++i] != NULL)
		if (!ft_strncmp(environ[i], args[1], nlen))
			if (environ[i][nlen] == '=')
				break ;
	if (environ[i] == NULL)
		;//Add new var str "VAR=args[2]"
	else
	{
		//environ[i] = 
	}
}

int			ftsh_unsetenv(char **args)
{

}*/

int			ftsh_env(char **args)
{
	int			i;

	i = -1;
	while (environ[++i] != NULL)
		ft_putendl(environ[i]);
	args = 0;
	return (0);
}
