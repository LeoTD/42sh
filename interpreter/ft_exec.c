#include "ft_sh.h"
#include "ast.h"
#include "libft.h"
//#include "_intepreter_dev.h"

/*
**	Execve(char *path, char **argv, char **environ);
**	First argument is the path of bin (e.g. /usr/bin/)
**	Second argument is the string of commands (e.g. "echo" "hello world");
**	Third argument is the global environment variable itself.
*/

extern char		**environ;

char			**strcat_path_with_file(char **all_bin_paths, t_ast *a)
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
	return (all_bin_paths);
}

int				find_number_of_paths(char *str)
{
	int 	i;
	int		number_of_paths;

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
	while (environ[i])
		i++;
	if (!(new = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (environ[i])
	{
		new[i] = ft_strdup(environ[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void			search_and_execute(char **all_bin_paths, t_ast *a)
{
	int		i;

	i = 0;
	while (all_bin_paths[i])
	{
		if (access(all_bin_paths[i], X_OK) != -1)
		{
			execve(all_bin_paths[i], a->tokens, environ);
			break;
		}
		i++;
	}
}
/*
**	Find the path variable inside the global extern char **environ.
**	String split the paths listed under the PATH variable.
**	Search through all paths to find the executable.
**	If found, execute. Else, do nothing and return.
*/

void			ft_exec(t_ast *a)
{
	int		i;
	char	**environment_copy;
	char	**all_bin_paths;
	char	*temp = NULL;

	i = 0;
	environment_copy = copy_environ_variables();
	while (environment_copy && environment_copy[i])
	{
		if (ft_strnstr(environment_copy[i], "PATH=", 5))
			temp = ft_strdup(environment_copy[i]);
		i++;
	}
	if (temp)
		all_bin_paths = strsplit_paths(temp + 5, 0, 0);
	else
	{
		ft_printf("Command %s not found\n", a->tokens[0]);
		return ;
	}
	all_bin_paths = strcat_path_with_file(all_bin_paths, a);
	search_and_execute(all_bin_paths, a);
}
