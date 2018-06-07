/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 20:39:09 by ckrommen          #+#    #+#             */
/*   Updated: 2018/06/06 22:03:54 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	ft_getwords(char const *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (*(s + i))
	{
		while (*(s + i) == c)
			i++;
		if (*(s + i) && *(s + i) != c)
			k++;
		while (*(s + i) && *(s + i) != c)
			i++;
	}
	return (k);
}

int		find_next(char *format, int *i)
{
	char	len;

	len = 0;
	while (format[*i])
	{
		if (format[*i] == '"')
		{
			while (format[++(*i)] != '"' && format[*i])
				len++;
			if (format[*i] == '"')
				len++;
		}
		if (ft_isspace(format[*i]))
			break ;
		len++;
		(*i)++;
	}
	return (len);
}

char	**split_args(char *format)
{
	char	**res;
	int		len;
	int		tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!(res = (char **)malloc(sizeof(char *) * ft_getwords(format, ' '))))
		return (NULL);
	while (format[i])
	{
		tmp = i;
		len = find_next(format, &i);
		res[k] = ft_strdup(ft_strsub(format, tmp, len));
		if (ft_isspace(format[i]))
			i++;
		printf("%s\n", res[k]);
		k++;
	}
	return (res);
}
