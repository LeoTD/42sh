#include "ft_sh.h"

int		arr_length(char **format)
{
	int i;
	
	i = 0;
	while (format[i])
		i++;
	return (i);
}

int		*tokenize(char **format)
{
	int *token;
	int i;

	i = 0;
	if (!(token = (int *)malloc(sizeof(int) * arr_length(format))))
		return (NULL);
	ft_bzero(token, arr_length(format));
	while (i < arr_length(format))
	{
		
	}
}
