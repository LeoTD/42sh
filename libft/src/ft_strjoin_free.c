/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:16:08 by ltanenba          #+#    #+#             */
/*   Updated: 2018/04/20 18:19:50 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int					ft_strjoin_free(char **dst, char *src)
{
	char			*tmp;

	tmp = *dst;
	*dst = ft_strjoin(*dst, src);
	if (!*dst)
		return (0);
	free(tmp);
	return (1);
}
