#include "ft_sh.h"

/*
 ** todo: free old key in setenv?
 ** TODO: handle case where key not already in env
 ** TODO: reserve extra space instead of reallocing entire env on every addition
 ** TODO: much memory leaked in builtin_env
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
	char	**store_env;
	char	**setenv_args;
	char	*eq;
	int		i;

	if (args[0] == NULL)
	{
		printenv();
		return ;
	}
	i = 0;
	store_env = ft_strdup_2d(g_environ);
	setenv_args = ft_memalloc(3 * sizeof(char *));
	while (args[i] && (eq = ft_strchr(args[i], '=')))
	{
		setenv_args[1] = ft_strdup(eq + 1);
		ft_strclr(eq);
		setenv_args[0] = ft_strdup(args[i++]);
		builtin_setenv(setenv_args);
	}
	if (i > 0 && args[i] == NULL)
		printenv();
	else if (args[i])
		parse_and_interpret(args + i);
	g_environ = store_env;
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
