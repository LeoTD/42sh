/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 07:56:33 by eliu              #+#    #+#             */
/*   Updated: 2018/07/09 23:16:10 by gmalpart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*ft_strjoin_newline(char const *s1, char const *s2)
{
	char	*tmp;
	int		len;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	tmp = ft_strnew(len);
	if (!tmp)
		return (0);
	while (*s1)
		*(tmp + ++i) = *(s1++);
	*(tmp + ++i) = '\n';
	while (*s2)
		*(tmp + ++i) = *(s2++);
	return (tmp);
}

/*
** replace the '\\' with a newline
** UPDATE: erasing '\\'
*/

char	*ft_strjoin_newline_back(char const *s1, char const *s2)
{
	char	*tmp;
	int		len;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2) - 1;
	tmp = ft_strnew(len);
	if (!tmp)
		return (0);
	while (*s1)
		*(tmp + ++i) = *(s1++);
	--i;
	while (*s2)
		*(tmp + ++i) = *(s2++);
	return (tmp);
}

int		cont_nbr_backslashes(char *str, int i)
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

char	*get_type_prompt(char value)
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

void	cont_chars_capsules(char *str, char schar, int *cont)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == schar)
		{
			if (i == 0)
				(*cont)++;
			else if (str[i - 1] == '\\')
				;
			else
				(*cont)++;
		}
		i++;
	}
}
