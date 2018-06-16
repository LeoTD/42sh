#include "ft_sh.h"

int			get_brackets_type(char a)
{
	if (a == '(')
		return (2);
	else if (a == ')')
		return (-2);
	else if (a == '[')
		return (3);
	else if (a == ']')
		return (-3);
	else if (a == '{')
		return (4);
	else if (a == '}')
		return (-4);
	else
		return (0);
}

#define IS_CAPSULE (str[i] == '\"' || str[i] == '\'' || str[i] == '`')
#define IS_BRACK_NL (str[i] == '\\')
#define STRNWL(x, y) ft_strjoin_newline(x, y)
#define ALLO_AND_FREE(dest, x, y) dest = STRNWL(x, y); free(x); free(y)

/*
** Checking for their correct ending ending quotes shouldn't be a problem
** becuase that was handle it in the last part of the parser
*/

int		check_brackets(char *str)
{
	int		i;
	float	res;
	char	inside_quotes;

	inside_quotes = 0;
	i = 0;
	res = 1.00;
	while (str[i])
	{
		if (IS_CAPSULE && ((i == 0) || (str[i - 1] != '\\')))
		{
			if (inside_quotes == 0)
				inside_quotes = 1;
			else
				inside_quotes = 0;
		}
		if (get_brackets_type(str[i]) > 0 && inside_quotes == 0)
			res = (res * 10) + get_brackets_type(str[i]);
		else if (get_brackets_type(str[i]) < 0 && inside_quotes == 0)
			res = (res + get_brackets_type(str[i])) / 10;
		if (res < 0)
			break ;
		i++;
	}
	if (res == 1.00)
		return (0);
	else
		return (1);
}

// boolean
// correct_syntax does the brackets on this string are correctly close


int			syntax_error(char *str)
{
	int		i;
	char	inside_quotes;

	inside_quotes = 0;
	i = -1;
	if (check_brackets(str) == 0)
		return (0);
	else
		return (1);
}
