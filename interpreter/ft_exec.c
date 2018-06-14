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

char	**strsplit_paths(char *str)
{
	int		i;
	int		number_of_paths;
	char	**paths;

	i = 0;
	number_of_paths = 0;
	while (str[i])
		if (str[i++] == ':')
			number_of_paths++;
	number_of_paths++;

//	fprintf(stderr, "inside strsplit_paths");
	paths = (char**)malloc(sizeof(char*) * (number_of_paths + 1));
	i = 0;
	int j;
	j = 0;
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
			// WARNING: DO NOT REMOVE THIS IF STATEMENT
			if (str[j])
				j++;
		}
	}
	paths[i] = ft_strdup(str);
	paths[i + 1] = NULL;
	i = 0;
//	printf("\n\n\n");
	while (paths[i])
	{
//		fprintf(stderr, "path=%s\n", paths[i]);
		i++;
	}
	return (paths);
}

/*
**	Creating a duplicate of environment so that we can search throuogh multiple paths.
*/

void	examine_path_file(char **str)
{
	for (int i = 0; str[i]; i++)
		fprintf(stderr, "%s\n", str[i]);
}

void	ft_exec(t_ast *a)
{
	int		i = 0;
	char	*environment_copy[256];

	while (environ[i])
	{
		environment_copy[i] = ft_strdup(environ[i]);
		i++;
	}
	environment_copy[i] = NULL;

	i = 0;
	char	*temp = NULL;
	while (environment_copy[i])
	{
		if (ft_strnstr(environment_copy[i], "PATH=", 5))
			temp = ft_strdup(environment_copy[i]);
		i++;
	}

	char	**all_bin_paths;
	char	**bin_paths_plus_file;
	
	if (temp)
	{
		all_bin_paths = strsplit_paths(temp + 5);
		bin_paths_plus_file = strsplit_paths(temp + 5);
	}
	else
	{
		fprintf(stderr, "\n\n\n\n\n ABORT ABORT ABORT \n\n\n\n\n\n");
		return ;
	}
	i = 0;
	while (bin_paths_plus_file[i])
	{
		bin_paths_plus_file[i] = ft_strjoin(bin_paths_plus_file[i], "/");
		bin_paths_plus_file[i] = ft_strjoin(bin_paths_plus_file[i], a->tokens[0]);
		i++;
	}
//	examine_path_file(bin_paths_plus_file);
	i = 0;
	char	*execute;


	execute = ft_strnew(0);
	int j = 0;
	
	while (bin_paths_plus_file[i])
	{
		if (access(bin_paths_plus_file[i], X_OK) != -1)
		{
			fprintf(stderr, "We can execute this!\n");
			fprintf(stderr, "executing: |%s|\n", bin_paths_plus_file[i]);
			while (a->tokens[j])
			{
					fprintf(stderr, "%s\n", a->tokens[j]);
					j++;
			}
			execve(bin_paths_plus_file[i], a->tokens, environ);
			break;
		}
		i++;
	}
//	fprintf(stderr, "\n\n\nOUTSIDE OF WHILE LOOP \n\n\n");
	if (access("./nfs/2016/e/eliu/starfleet/starfleet_github/leo42sh/interpreter/helpers/write_and_exit", X_OK))
		{
//			fprintf(stderr, "\n\n\n MADE IT INSIDE \n\n\n");
			execve("/nfs/2016/e/eliu/starfleet/starfleet_github/leo42sh/interpreter/helpers/write_and_exit", a->tokens, environ);
		}
	else
		fprintf(stderr, "else statement\n");	
/*
	// while trying all paths, if found an executable binary, execute, break and exit
	// if not, break and exit
*/
//	execvp(a->tokens[0], a->tokens);

	// Iterate through environ g_variable to see if PATH= exists.
	// DONE	

	// If it does, store all possible paths inside 2d char array.
	// DONE

	// See if the executable is inside the path
	// CURRENT

	// Concatenate the name of the PATH + EXECUTABLE_NAME eg: /usr/bin/ls
	// Use access to see if it can be accessible, otherwise move onto next bin and see if can be found or executed
	// if execute, stop search and return 

	// If it is, execute the function with execve.

	// If not, return and do nothing.

//	printf("\n eliu working dev :3 \n");




}
