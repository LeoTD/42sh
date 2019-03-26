/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 07:56:19 by eliu              #+#    #+#             */
/*   Updated: 2018/06/20 08:41:54 by eliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	g_builtin_env(char **args)
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
		g_builtin_setenv(setenv_args);
	}
	if (i > 0 && args[i] == NULL)
		printenv();
	else if (args[i])
		parse_and_interpret(args + i);
	g_environ = store_env;
}

void	g_builtin_setenv(char **args)
{
	char	*val;

	if (args[0] == NULL)
	{
		printenv();
		return ;
	}
	val = args[1] == NULL ? "" : args[1];
	ft_set_env(args[0], val, g_environ);
}

void	g_builtin_unsetenv(char **args)
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
			ft_swap_str(g_environ + i, g_environ + envsize - 1);
			free(g_environ[envsize - 1]);
			g_environ[envsize - 1] = NULL;
			return ;
		}
		++i;
	}
}
