/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:48:08 by ckrommen          #+#    #+#             */
/*   Updated: 2018/02/23 16:38:56 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** argument prototype: %[flags][width/margin][.precision][hh|h|l|ll|j|z]type
**
** flags:			'+' || '-' || ' ' || '#' || '0';
**
** width/margin:	min amount of displayed digits, does not cut digits if less,
**					fill with spaces on the left side;
**					if '*' added it's necessary to pass one more parameter with
**					a number of spaces before the actual parameter;
**
** .precision:		for diouxX min amount of digits, fill with 0 is necessary;
**					for eEf amount of digits after dot;
**					for gG amount of all digits, if bigger displays number;
**					for sS max amount of characters;
**					if '*' added is necessary to pass one more parameter with a
**					number of spaces before the actual parameter;
**
** hh|h|l|ll|j|z|q:	default values' modification:
**						hh:	for idouxX - char;
**						h:	for idouxX - short int;
**						l:	for idouxX - long int, for feE - double;
**						ll:	for idouxX - long long int;
**						j:	for idouxX - intmax_t;
**						z:	for idouxX - size_t;
**						q:	for CS - prints Unicode
*/

/*
** Determines which conversion to be done with the given % arg
** sSpdDioOuUxXcC
**  %d %i     Decimal signed integer.
**  %o      Octal integer.
**  %x %X     Hex integer.
**  %u      Unsigned integer.
** %c      Character.
** %s      String.
** %c       char
** %p        pointer.
** No argument expected.
** % %%. No argument expected.
*/

int		find_flag(t_tools tools, va_list ap)
{
	int ret;

	if (PER && !PREC && TYPE != '%' && TYPE != 'c' &&
		TYPE != 'C' && TYPE != 'd' && TYPE != 'o')
	{
		va_arg(ap, void *);
		return (print_buffer(tools));
	}
	else if ((TYPE == 'S' && WIDE) || (TYPE == 'C' && WIDE) ||
			(TYPE == 's' && FORM == 3) || (TYPE == 'c' && FORM == 3))
		ret = convert_wchar(tools, ap, 0);
	else if (TYPE == 's' || TYPE == 'c' || TYPE == '%' ||
			(TYPE == 'C' && !WIDE) || (TYPE == 'S' && !WIDE))
		ret = convert_char(tools, ap);
	else if (TYPE == 'd' || TYPE == 'i' || (TYPE == 'D' && FORM))
		ret = convert_int(tools, ap);
	else if (TYPE == 'p' || TYPE == 'x' || TYPE == 'X' ||
			TYPE == 'o' || TYPE == 'O')
		ret = convert_ptr(tools, ap);
	else if (TYPE == 'u' || TYPE == 'U' || (TYPE == 'D' && !FORM))
		ret = convert_ull(tools, ap);
	else
		ret = 0;
	return (ret);
}

/*
** Handles every flag preceding the conversion character and assigns tools to it
*/

int		parse_flag(char *format, t_tools tools, int *i, va_list ap)
{
	while (!ft_findchar(format[*i], "sSpdDioOuUxXcC") && format[(*i)++])
	{
		if (FLAGS(format[*i]))
			tools = assign_flags(tools, format, i);
		else if (format[*i] == 'w')
			WIDE = TRUE;
		else if (ft_isdigit(format[*i]))
			WIDTH = ft_atoi(ft_substr(*i, format));
		else if (format[*i] == '.' && (PER = TRUE))
		{
			if ((format[*i + 1] && ft_isdigit(format[*i + 1])))
				PREC = ft_atoi(ft_substr(*i + 1, format));
		}
		else if (format[*i] == '*')
			va_arg(ap, int);
		else if (FORMAT(format[*i]))
			tools = assign_format(tools, format, i);
		else if (format[*i] == '%')
			break ;
		while ((ft_isdigit(format[*i + 1]) && format[*i + 1]) &&
				(WIDTH || PREC))
			(*i)++;
	}
	TYPE = format[*i];
	return (find_flag(tools, ap));
}

/*
** parses orignal format string until a % char is found
*/

int		parse_format(char *format, t_tools tools, va_list ap)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			ft_putchar(format[i]);
			ret++;
		}
		else
		{
			ret += parse_flag(format, tools, &i, ap);
			tools = reset_tools();
		}
		i++;
	}
	return (ret);
}

int		ft_printf(const char *format, ...)
{
	t_tools tools;
	va_list ap;
	int		ret;

	va_start(ap, format);
	tools = reset_tools();
	ret = parse_format((char *)format, tools, ap);
	va_end(ap);
	return (ret);
}
