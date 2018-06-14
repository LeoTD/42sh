#include "ft_sh.h"


/*
** ASSUMING THAT ENV, the one we are modiying
*/

// logic inside_quotes
// no idea about globbing affect this shit

#define IS_ENV_VAR(x, y) (x[y] == '$')

int			nbr_positions(char *str)
{
	int		i;
	int		nbr_positions;

	nbr_positions = 0;
	i = -1;
	while (str[++i])
	{
		// check for char
		// check for COMPREHENSIVE WORD AFTER THAT
		if (IS_ENV_VAR(str, i) && ((i == 0) || (str[i - 1] != '\\')))
			if ()
	}
	return (nbr_positions);
}

int			*look_for_positions(char *str)
{
	int		nbr_positions(char *str);

	nbr_positions(str);
	if ()
}

void		look_and_replace_vars(char *str, char **temp)
{
	int		i;
	int		*positions;

	positions = look_for_positions(str);
	if (positions == NULL)
	{
		*temp = str;
		return ;
	}
	i = -1;
	// look for positions - checking that they are not in QUOTES or have a
	// backslash behind them
	while()
	
}

char		*replace_env_vars(char *str)
{
	char	*temp;

	temp = NULL;
	look_and_replace_vars(str, &(temp));
	return (temp);
}
