/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:48:08 by ltanenba          #+#    #+#             */
/*   Updated: 2018/03/30 00:18:04 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int val, int base)
{
	char	cipher[17];
	char	tmp[33];
	int		i;
	long	n;

	if (val == 0)
		return (ft_strdup("0"));
	if (base == 10)
		return (ft_itoa(val));
	n = val;
	if (n < 0)
		n *= -1;
	ft_strcpy(cipher, "0123456789ABCDEF");
	i = -1;
	while (++i < 33)
		tmp[i] = '\0';
	i = -1;
	while (n > 0 && i < 33)
	{
		tmp[++i] = cipher[n % base];
		n /= base;
	}
	return (ft_strrev(tmp));
}
