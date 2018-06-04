/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numberconv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 20:09:50 by ckrommen          #+#    #+#             */
/*   Updated: 2018/02/23 20:13:05 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Int value to Hexadecimal
*/

char	*ft_itoabase(unsigned long long int nbr, t_tools tools,
					char *str, int base)
{
	int i;

	i = 0;
	if (!nbr)
		str[i] = '0';
	if (TYPE == 'x' || TYPE == 'p' || TYPE == 'o')
	{
		while (nbr != 0)
		{
			str[i++] = "0123456789abcdef"[nbr % base];
			nbr /= base;
		}
	}
	else
		while (nbr != 0)
		{
			str[i++] = "0123456789ABCDEF"[nbr % base];
			nbr /= base;
		}
	if (HASH || TYPE == 'p')
		hash(tools, str);
	return (ft_strrev(str));
}

/*
** ULL to ascii
*/

char	*ft_ulltoa(__uint64_t nbr)
{
	int			length;
	__uint64_t	sign;
	char		*str;

	sign = nbr;
	length = 1;
	while (sign /= 10)
		length++;
	str = ft_strnew(length);
	if (!str)
		return (NULL);
	while (--length >= 0)
	{
		str[length] = (nbr >= 10) ? (nbr % 10) + 48 : nbr + 48;
		nbr /= 10;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}

/*
** Unicode to ascii
*/

char	*ft_unitoa(wint_t wstr)
{
	char *str;

	str = ft_strnew(5);
	if (wstr <= 0x7F)
		str[0] = wstr;
	else if (wstr <= 0x7FF)
	{
		str[0] = (((wstr >> 6) & 0x1F) | 0xC0);
		str[1] = (((wstr >> 0) & 0x3F) | 0x80);
	}
	else if (wstr <= 0xFFFF)
	{
		str[0] = (((wstr >> 12) & 0x0F) | 0xE0);
		str[1] = (((wstr >> 6) & 0x3F) | 0x80);
		str[2] = (((wstr >> 0) & 0x3F) | 0x80);
	}
	else if (wstr < 0x10FFFF)
	{
		str[0] = (((wstr >> 18) & 0x07) | 0xF0);
		str[1] = (((wstr >> 12) & 0x3F) | 0x80);
		str[2] = (((wstr >> 6) & 0x3F) | 0x80);
		str[3] = (((wstr >> 0) & 0x3F) | 0x80);
	}
	return (str);
}
