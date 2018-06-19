#include "ft_sh.h"

/*
 ** todo: free old key in setenv?
 ** TODO: handle case where key not already in env
 ** TODO: reserve extra space instead of reallocing entire env on every addition
 */

void	printenv(void)
{
	int	i;

	i = 0;
	while (g_environ[i])
		ft_putendl(g_environ[i++]);
}

void	add_env_entry(char *entry)
{
	size_t	envsize;
	char	**new_env;
	int		i;

	envsize = arr_length(g_environ);
	new_env = ft_memalloc((envsize + 2) * sizeof(*new_env));
	i = 0;
	while (g_environ[i])
	{
		new_env[i] = g_environ[i];
		++i;
	}
	new_env[i] = entry;
	free(g_environ);
	g_environ = new_env;
}

void	builtin_env(char **args)
{
	if (args[0] == NULL)
	{
		printenv();
		return ;
	}
	exit(0);
	args = NULL;
}

void	builtin_setenv(char **args)
{
	int		i;
	size_t	keylen;
	char	*entry;
	char	*val;

	if (args[0] == NULL)
	{
		printenv();
		return ;
	}
	val = args[1] == NULL ? "" : args[1];
	i = 0;
	keylen = ft_strlen(args[0]);
	entry = ft_strjoinv(2, "=", args[0], val);
	while (g_environ[i])
	{
		if (!(ft_strncmp(g_environ[i], entry, keylen + 1)))
		{
			g_environ[i] = entry;
			return ;
		}
		++i;
	}
	add_env_entry(entry);
}

void	swap_entry_positions(char **ary, int i, int j)
{
	char *tmp;

	tmp = ary[i];
	ary[i] = ary[j];
	ary[j] = tmp;
}

void	builtin_unsetenv(char **args)
{
	int		i;
	size_t	keylen;
	int		envsize;

	if (!args[0])
	{
		ft_putstr_fd("Too few arguments\n", 2);
		return ;
	}
	i = 0;
	envsize = arr_length(g_environ);
	keylen = ft_strlen(args[0]);
	while (i < envsize)
	{
		if (!(ft_strncmp(g_environ[i], args[0], keylen))
				&& g_environ[i][keylen] == '=')
		{
			swap_entry_positions(g_environ, i, envsize - 1);
			free(g_environ[envsize - 1]);
			g_environ[envsize - 1] = NULL;
			return ;
		}
		++i;
	}
}
