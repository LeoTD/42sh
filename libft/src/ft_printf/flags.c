/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 10:46:45 by ckrommen          #+#    #+#             */
/*   Updated: 2018/02/22 21:15:27 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** use the tools struct to deal with the width / zero flags
*/

void		width(char *str, t_tools tools, char *arg)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if ((arg[0] == '+' || arg[0] == '-' || arg[0] == 32) && ZERO)
	{
		str[i] = (arg[0] == '+') ? '+' : '-';
		str[i] = (arg[0] == ' ') ? 32 : str[i];
		i++;
		j++;
	}
	while (MINUS == FALSE && WIDTH-- > (int)ft_strlen(arg))
		str[i++] = ZERO ? '0' : 32;
	if ((arg[0] == '+' || arg[0] == '-' || arg[0] == 32) && !ZERO)
	{
		str[i] = (arg[0] == '+') ? '+' : '-';
		str[i] = (arg[0] == ' ') ? 32 : str[i];
		i++;
		j++;
	}
	while (arg[j])
		str[i++] = arg[j++];
	while (MINUS == TRUE && WIDTH-- > (int)ft_strlen(arg))
		str[i++] = ZERO ? '0' : 32;
}

/*
** use the tools struct to deal with precision
*/

char		*precision(t_tools tools, char *arg, int j)
{
	int		i;
	char	*str;

	str = ft_strnew(PREC + ft_strlen(arg));
	ft_bzero(str, PREC + ft_strlen(arg));
	if (SPACE && !NEG)
		str[0] = ' ';
	else if (PLUS && !NEG)
		str[0] = '+';
	else if (NEG)
		str[0] = '-';
	i = str[0] == ' ' || str[0] == '-' || str[0] == '+' ? 1 : 0;
	while (PREC > (int)ft_strlen(arg))
	{
		str[i++] = (ZERO || ft_findchar(TYPE, "iudxXoO")) ? '0' : 32;
		PREC--;
	}
	while (arg[j] && PREC > 0)
	{
		str[i++] = arg[j++];
		if (!ft_findchar(TYPE, "iudxXoO"))
			PREC--;
	}
	return (str);
}

/*
** Handle hash flag
*/

void		hash(t_tools tools, char *arg)
{
	int i;

	i = 0;
	if (TYPE == 'x' || TYPE == 'X')
	{
		arg[ft_strlen(arg)] = TYPE == 'X' ? 'X' : 'x';
		arg[ft_strlen(arg)] = '0';
	}
	else if (TYPE == 'p')
	{
		arg[ft_strlen(arg)] = 'x';
		arg[ft_strlen(arg)] = '0';
	}
	else if (TYPE == 'o' || TYPE == 'O')
		arg[ft_strlen(arg)] = '0';
}

/*
** Assigns flags to t_tools
*/

t_tools		assign_flags(t_tools tools, char *format, int *i)
{
	if (format[*i] == ' ')
		SPACE = TRUE;
	else if (format[*i] == '+')
		PLUS = TRUE;
	else if (format[*i] == '-')
		MINUS = TRUE;
	else if (format[*i] == '0')
		ZERO = TRUE;
	else if (format[*i] == '#')
		HASH = TRUE;
	return (tools);
}

/*
** print flag as normal string if unsupported flags found
*/

int			ft_printnorm(char *str, int *i)
{
	while (str[*i] != '%')
		--(*i);
	return (1);
}
