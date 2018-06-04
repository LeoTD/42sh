/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:38:31 by ltanenba          #+#    #+#             */
/*   Updated: 2018/03/30 00:22:58 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *src)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	len = ft_strlen(src);
	if (!(tmp = ft_strnew(len)))
		return (0);
	while (*(src + ++i))
		*(tmp + (len - i - 1)) = *(src + i);
	return (tmp);
}
