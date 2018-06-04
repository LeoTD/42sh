/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:33:26 by ltanenba          #+#    #+#             */
/*   Updated: 2018/03/30 00:23:09 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	tmp[13];
	int		i;
	int		is_neg;

	i = -1;
	is_neg = 0;
	while (++i < 13)
		tmp[i] = '\0';
	if (n < 0 && (is_neg = 1))
		n *= -1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	i = -1;
	while (n > 0)
	{
		tmp[++i] = n % 10 + '0';
		n /= 10;
	}
	if (is_neg)
		tmp[++i] = '-';
	return (ft_strrev(tmp));
}
