/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 07:56:25 by eliu              #+#    #+#             */
/*   Updated: 2018/06/27 00:41:57 by eliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ast.h"
#include "libft.h"

/*
**	Execve(char *path, char **argv, char **environ);
**	First argument is the path of bin (e.g. /usr/bin/)
**	Second argument is the string of commands (e.g. "echo" "hello world");
**	Third argument is the global environment variable itself.
*/

int				find_number_of_paths(char *str)
{
	int	i;
	int	number_of_paths;

	i = 0;
	number_of_paths = 1;
	while (str[i])
	{
		if (str[i] == ':')
			number_of_paths++;
		i++;
	}
	return (number_of_paths);
}

char			**strsplit_paths(char *str, int i, int j)
{
	int		number_of_paths;
	char	**paths;

	number_of_paths = find_number_of_paths(str);
	paths = (char**)malloc(sizeof(char*) * (number_of_paths + 1));
	while (number_of_paths != 1)
	{
		while (str[j])
		{
			if (str[j] == ':')
			{
				paths[i] = ft_strndup(str, j);
				str += j + 1;
				j = 0;
				number_of_paths--;
				i++;
			}
			if (str[j])
				j++;
		}
	}
	paths[i] = ft_strdup(str);
	paths[i + 1] = NULL;
	return (paths);
}

/*
**	Creating a duplicate environment so that we can search through paths.
*/

char			**copy_environ_variables(void)
{
	int			i;
	char		**new;

	i = 0;
	while (g_environ[i])
		i++;
	if (!(new = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (g_environ[i])
	{
		new[i] = ft_strdup(g_environ[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

/*
** todo: free all_bin_paths ?
*/

void			search_and_execute(char **all_bin_paths, t_ast *a)
{
	int		i;
	char	*temp;

	i = 0;
	while (all_bin_paths[i])
	{
		temp = all_bin_paths[i];
		all_bin_paths[i] = ft_strjoin(all_bin_paths[i], "/");
		free(temp);
		temp = all_bin_paths[i];
		all_bin_paths[i] = ft_strjoin(all_bin_paths[i], a->tokens[0]);
		free(temp);
		i++;
	}
	i = -1;
	while (all_bin_paths[++i])
		if (access(all_bin_paths[i], X_OK) != -1)
			execve(all_bin_paths[i], a->tokens, g_environ);
	ft_printf("42sh: command not found: %s\n", a->tokens[0]);
}

/*
**	Find the path variable inside the global extern char **environ.
**	String split the paths listed under the PATH variable.
**	Search through all paths to find the executable.
**	If found, execute. Else, do nothing and return.
*/

void			env_exec(t_ast *a)
{
	int		i;
	char	**environment_copy;
	char	*temp;

	extract_redirs(a);
	handle_redirs(a);
	if (!ft_strcmp(a->tokens[0], g_builtin_str[BIN_ECHO]))
		g_builtin_echo(a->tokens + 1);
	if (access(a->tokens[0], X_OK) != -1)
		execve(a->tokens[0], a->tokens, g_environ);
	else
	{
		i = -1;
		temp = NULL;
		environment_copy = copy_environ_variables();
		while (environment_copy && environment_copy[++i])
			if (ft_strnstr(environment_copy[i], "PATH=", 5))
				temp = ft_strdup(environment_copy[i]);
		if (temp)
			search_and_execute(strsplit_paths(temp + 5, 0, 0), a);
	}
	_exit(1);
}
