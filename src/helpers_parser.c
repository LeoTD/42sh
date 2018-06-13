#include "ft_sh.h"

int			cont_nbr_backslashes(char *str, int i)
{
	int		nbr_backslashes;

	nbr_backslashes = 0;
	i = i - 1;
	while (i >= 0 && str[i] == '\\')
	{
		i--;
		nbr_backslashes++;
	}
	return (nbr_backslashes);
}

char		*get_type_prompt(char value)
{
	if (value == DQUOTE)
		return (DQUOTE_PROMPT);
	else if (value == QUOTE)
		return (QUOTE_PROMPT);
	else if (value == BQUOTE)
		return (BQUOTE_PROMPT);
	else if (value == SUBSH)
		return (SUBSH_PROMPT);
	else
		return (NULL);
}
