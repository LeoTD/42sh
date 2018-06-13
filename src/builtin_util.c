#include "ft_sh.h"

/*
** Array declarations for builtins.
*/

char		*builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int			(*builtin_func[])(char **args) = {
	&ftsh_cd,
	&ftsh_help,
	&ftsh_exit
};

/*
** Takes id as given by is_builtin()
** and char **args, where args[0] contains the cmd
** and args[1+] contain arguments.
*/

int			run_builtin(int id, char **args)
{
	return (*builtin_func[id])(args);
}

/*
** Returns id of builtin or -1 if there's no match.
*/

int			is_builtin(char *str)
{
	int			i;

	i = -1;
	while (++i < 3) //Number of builtins
		if (ft_strcmp(str, builtin_str[i]) == 0)
			return (i);
	return (-1);
}
