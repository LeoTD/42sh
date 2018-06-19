#include "ft_sh.h"


/*
** ASSUMING THAT ENV, the one we are modiying
*/

// logic inside_quotes
// no idea about globbing affect this shit

#define IS_ENV_VAR(x, y) (x[y] == '$')
#define IS_CAPSULE (str[i] == '\"' || str[i] == '\'' || str[i] == '`')

int			nbr_positions(char *str)
{
	int		i;
	int		nbr_positions;
	char	inside_quotes;

	inside_quotes = 0;
	nbr_positions = 0;
	i = -1;
	while (str[++i])
	{
		// check for char
		// check for COMPREHENSIVE WORD AFTER THAT
		if (IS_CAPSULE && ((i == 0) || (str[i - 1] != '\\')))
			if (inside_quotes == 0)
				inside_quotes = 1;
			else
				inside_quotes = 0;
		else if (IS_ENV_VAR(str, i) && ((i == 0) || (str[i - 1] != '\\')) \
				&& (inside_quotes == 0) && \
				(str[i + 1] != '\0' || str[i] != '$'))
			nbr_positions++;
	}
	return (nbr_positions);
}

int			*look_for_positions(char *str)
{
	int		*positions;
	int		i;
	char	inside_quotes;
	int		e;

	e = 0;
	i = -1;
	inside_quotes = 0;
	positions = (int*)ft_memalloc(sizeof(int) * nbr_positions(str));
	while (str[++i])
	{
		if (IS_CAPSULE && ((i == 0) || (str[i - 1] != '\\')))
			if (inside_quotes == 0)
				inside_quotes = 1;
			else
				inside_quotes = 0;
		else if (IS_ENV_VAR(str, i) && ((i == 0) || (str[i - 1] != '\\')) \
				&& (inside_quotes == 0) \
				(str[i + 1] != '\0' || str[i + 1] != '$'))
		{
			positions[e] = i;
			e++;
		}
	}
	return (positions);
}

// verify is the variable is a valid one
// multiple $$$$ need to be handle,
// 	^BEHAVIOR: the shit is going to replace the 
// a NAME is defined when the string touch a WHITESPACE
// 
// 											POSITIONS
//	read and look for variables(char *str, int *i)
//		using the positions, determinate a length to the words
//		so you will have two int *, one for the initial postio
//					and another one for the len of the int*
//					INITIAL_POST		LEN_POSTIONS
//
//
//	AFTER THIS PART IS DONE, REMOVE ALL '\' AND '\n'
//	Maybe just erase all of the '\' and just the subsequent '\' followed by
//	a '\n'

#define IS_WHITESPACES(x, y) (x[y] == '\n' || x[y] == '\t' || x[y] == ' ')
#define NO_WHITESPACES(x, y) (x[y] != '\n' && x[y] != '\t' && x[y] != ' ')
#define NO_CAPSULE(x, y) (x[y] != '\"' && x[y] != '\'' && x[y] != '`')

int			*length_of_envars(char *str, int *positions, int size_positions)
{
	// all those alone ints can be changed to an array of ints pendejada[4]
	int		*length_of_vars;
	int		i;
	int		e;
	int		length;

	if (size_positions <= 0)
		return (NULL);
	length_of_vars = ft_memalloc(sizeof(int) * size_positions);
	i = -1;
	while(++i < size_positions)
	{
		length = 0;
		e = positions[i];
		while(NO_WHITESPACES(str, e) && NO_CAPSULE(str, e) &&\
			str[e] != '\0')
		{
			length++;
			e++;
		}
		length_of_vars = length;
	}
	// a while throught the positions to find the end or end of the string
	// basically str[i] != WHITESPACES || str[i] != '\0'
	return (length_of_vars);
}



void		look_and_replace_vars(char *str, char **temp)
{
	int		i;
	int		*positions;
	int		*length_positions;

	*temp = str;
	positions = look_for_positions(str);
	if (positions == NULL)
		return ;
	length_positions = length_of_envars;
	if (length_positions == NULL)
		return ;
	i = -1;
	// look for positions - checking that they are not in QUOTES or have a
	// backslash behind them
	*temp = ;// function that handle this shit
	free(positions);
}

char		*replace_env_vars(char *str)
{
	char	*temp;

	temp = NULL;
	look_and_replace_vars(str, &(temp));
	return (temp);
}