/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:33:49 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/27 14:49:06 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*tmp;

	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		return (0);
	if (!content)
	{
		tmp->content_size = 0;
		tmp->content = 0;
	}
	else
	{
		tmp->content_size = content_size;
		if (!(tmp->content = (void *)malloc(content_size)))
			return (0);
		tmp->content = ft_memcpy(tmp->content, content, content_size);
	}
	tmp->next = 0;
	return (tmp);
}
