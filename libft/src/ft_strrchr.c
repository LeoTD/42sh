/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 21:27:07 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/28 17:18:49 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(s);
	while (++i <= len)
		if (*(s + (len - i)) == (char)c)
			return ((char *)(s + (len - i)));
	return (0);
}
