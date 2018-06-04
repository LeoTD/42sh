/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:19:45 by ckrommen          #+#    #+#             */
/*   Updated: 2018/02/23 15:47:49 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** used to print a space buffer if only a period is provided for precision
*/

int		print_buffer(t_tools tools)
{
	int ret;

	ret = 0;
	while (WIDTH--)
	{
		ft_putchar(ZERO ? '0' : 32);
		ret++;
	}
	return (ret);
}

/*
** Prints width and height for special cases
*/

int		ft_specialbuffer(t_tools tools, char *arg)
{
	int ret;

	ret = 0;
	if (!WIDTH)
		WIDTH = 1;
	while (--WIDTH && !MINUS)
	{
		ret++;
		ft_putchar(ZERO ? '0' : 32);
	}
	ft_putchar(arg[0]);
	ret++;
	while (WIDTH-- && MINUS)
	{
		ret++;
		ft_putchar(ZERO ? '0' : 32);
	}
	return (ret);
}

/*
** Fix memory signature for 0 padding on hexadecimal
*/

void	ft_alignptr(char *str, t_tools tools)
{
	int i;

	i = 0;
	if (str[i] == '0')
	{
		while (str[i] != 'x' && str[i] != 'X')
			i++;
		str[i] = '0';
		str[1] = TYPE == 'X' ? 'X' : 'x';
	}
}

/*
** putchar that returns 1
*/

int		ft_retchar(char c)
{
	write(1, &c, 1);
	return (1);
}
