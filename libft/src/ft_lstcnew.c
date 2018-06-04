/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 06:04:55 by ltanenba          #+#    #+#             */
/*   Updated: 2018/03/30 21:35:31 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_clist		*ft_lstcnew(void *content, size_t content_size, char *id)
{
	t_clist	*tmp;

	tmp = malloc(sizeof(t_clist));
	if (!tmp)
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
	tmp->id = ft_strdup(id);
	tmp->up = tmp;
	tmp->down = tmp;
	tmp->left = tmp;
	tmp->right = tmp;
	tmp->head = 0;
	return (tmp);
}
