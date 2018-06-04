/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:50:12 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/22 15:50:15 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *str, char (*funk)(char))
{
	char	*tmp;
	int		i;

	i = -1;
	if (!str || !funk)
		return (0);
	tmp = ft_strnew(ft_strlen(str));
	if (!tmp)
		return (0);
	while (*(str + ++i))
		*(tmp + i) = funk(*(str + i));
	return (tmp);
}
