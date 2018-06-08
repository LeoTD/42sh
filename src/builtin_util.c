#include "ft_sh.h"

/*
** Function Declarations for builtins.
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

int			run_builtin(int id, char **args)
{
	return (*builtin_func[id])(args);
}

int			is_builtin(char *str)
{
	int			i;

	i = -1;
	while (++i < 3) //Number of builtins
		if (ft_strcmp(str, builtin_str[i]) == 0)
			return (i);
	return (-1);
}
