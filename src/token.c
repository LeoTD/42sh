/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 07:57:09 by eliu              #+#    #+#             */
/*   Updated: 2018/06/20 07:57:10 by eliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "ast.h"

char	*g_nodetype_names[] = {
	[SEP] = ";",
	[AND] = "&&",
	[OR] = "||",
	[PIPE] = "|",
	[NEGATE] = "!",
	[CMD] = NULL
};

int		is_operator(char *arg)
{
	int i;

	i = 0;
	while (i <= MAX_CMDTYPE)
	{
		if (g_nodetype_names[i] && !ft_strcmp(arg, g_nodetype_names[i]))
			return (i);
		i++;
	}
	return (-1);
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
		if (is_operator(format[i]) != -1)
			token[i] = is_operator(format[i]);
		else
			token[i] = CMD;
		i++;
	}
	return (token);
}
