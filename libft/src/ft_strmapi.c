/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:12:52 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/22 15:50:47 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*funk)(unsigned int, char))
{
	char				*tmp;
	unsigned int		i;

	i = 0;
	if (!str || !funk)
		return (0);
	tmp = ft_strnew(ft_strlen(str));
	if (!tmp)
		return (0);
	while (*(str + i))
	{
		*(tmp + i) = funk(i, *(str + i));
		i++;
	}
	return (tmp);
}
