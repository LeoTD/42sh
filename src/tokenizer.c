#include "ft_sh.h"

#define WHITESPACES (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
#define IS_WHITESPACES ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')

// things to considerer is that 

int		is_a_token(char a, char b)
{
	if (a == ';')
		return (1);
	else if (a == '&' && b == '&')
		return (1);
	else if (a == '|')
		return (1);
	else if (a == '|' && b == '|')
		return (1);
	else if (a == '!')
		return (1);
	else
		return (0);
}

int		end_of_qmarks(char *str, int *i)
{
	while (str[*i])
}

int		nrb_islands(char *str)
{
	int		i;
	int		nbr_islands;

	nbr_islands = 0;
	i = 0;
	while (str[i])
	{
		while (IS_WHITESPACES)
			i++;
		if (WHITESPACES)
		{
			nbr_islands++;
			if (str[i] == '"')
				if (end_of_qmarks(str, &i) == -1)
			while(WHITEiSPACES)
				i++;
		}
	}
	return (nbr_islands);
}

int		*get_island(char *str)
{
	int		i;
	int		*islands;
	
	islands = ft_memalloc(sizeof(int) * nbr_islands(str));
	i = 0;
	while(str[i])
	{
		
	}
	return (islands);
}

int		ft_get_n_words(char *str)
{
	int		i;
	int		words;
	int		*islands;

	islands = get_island(str);
	i = -1;
	// you iterate with the islands
	// everything is splitted with spaces and tabs
	while(str[i])
	{
		if (str[i] == )
	}
	free(islands);
	return (words);
}

char	**tokenizer(char *str)
{
	char	**res;
	int		i;

	i = 0;
	res = ft_memalloc(sizeof(char*) * ft_get_n_words(str));
	while(str[i])
	{
		if()
	}
	return (res);
}
