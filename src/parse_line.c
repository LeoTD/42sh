#include "ft_sh.h"

#define IS_CAPSULE (str[i] == '\"' || str[i] == '\'' || str[i] == '`')
#define IS_BRACK_NL (str[i] == '\\')
#define STRNWL(x, y) ft_strjoin_newline(x, y)
#define ALLO_AND_FREE(dest, x, y) dest = STRNWL(x, y); free(x); free(y)

char		*concatinated_string(char type)
{
	char	*temp;
	char	*concat;
	char	*join;
	int		cont_nbr_capsule;

	cont_nbr_capsule = 0;
	temp = ft_prompt(get_type_prompt(type));
	cont_chars_capsules(temp, type, &(cont_nbr_capsule));
	while (cont_nbr_capsule % 1 == 1 || cont_nbr_capsule == 0)
	{
		concat = ft_prompt(get_type_prompt(type));
		join = ft_strjoin_newline(temp, concat);
		free(temp);
		free(concat);
		temp = join;
		cont_nbr_capsule = 0;
		cont_chars_capsules(temp, type, &(cont_nbr_capsule));
	}
	return (temp);
}

/*
**	recursively solution for the inhbitors in the '\'
*/

#define LAST_CHAR_BSLASH(x, i) (ft_strequ(ft_strstr(x + i, "\\"), "\\") == 1)
#define N_SLASH(x, i) cont_nbr_backslashes(x, i)

char		*concatined_newline(int i)
{
	char	*temp;
	char	*concat;
	char	*join;
	int		e;
	char	*extra;

	e = -1;
	temp = ft_prompt(NEWLINE_PROMPT);
	if (LAST_CHAR_BSLASH(temp, i) && ((N_SLASH(temp, i) % 2 == 0) || \
		(N_SLASH(temp, i) == 0)))
	{
		concat = ft_prompt(NEWLINE_PROMPT);
		while (concat[++e])
			if (concat[e] == '\\')
				if (LAST_CHAR_BSLASH(concat, e) && \
				((N_SLASH(concat, e) % 2 == 0) || (N_SLASH(concat, e) == 0)))
				{
					extra = concatined_newline(e);
					ALLO_AND_FREE(join, concat, extra);
					concat = join;
				}
		ALLO_AND_FREE(join, temp, concat);
		temp = join;
	}
	return (temp);
}

void		wrap_quotes(char **str, int i)
{
	char	get_capsule;
	int		cont_nbr_capsule;
	char	*concat;
	char	*tmp;

	cont_nbr_capsule = 0;
	get_capsule = (*str)[i];
	cont_chars_capsules(*str, get_capsule, &(cont_nbr_capsule));
	if (cont_nbr_capsule % 2 == 1)
	{
		concat = concatinated_string(get_capsule);
		ALLO_AND_FREE(tmp, *str, concat);
		*str = tmp;
	}
}

void		is_capsule_incomplete(char *str, char **temp)
{
	int		i;
	int		cont_nbr_capsule;
	char	*concat;
	char	*tmp;

	i = -1;
	cont_nbr_capsule = 0;
	while (str[++i])
	{
		if (IS_CAPSULE)
			wrap_quotes(&(str), i);
		else if (IS_BRACK_NL)
			if (LAST_CHAR_BSLASH(str, i) && ((N_SLASH(str, i) % 2 == 0) || \
			(N_SLASH(str, i) == 0)))
			{
				concat = concatined_newline(i);
				ALLO_AND_FREE(tmp, str, concat);
				str = tmp;
			}
	}
	*temp = str;
}

char		*parse_line(char *str)
{
	char	*temp;

	temp = NULL;
	is_capsule_incomplete(str, &(temp));
	return (temp);
}
