#include "ft_sh.h"

int			cont_nbr_backslashes(char *str, int i)
{
	int		nbr_backslashes;

	nbr_backslashes = 0;
	while (str[--i] == '\\')
		nbr_backslashes++;
	return (nbr_backslashes);
}
