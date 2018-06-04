/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:54:27 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/28 22:23:18 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*funk)(t_list *elem))
{
	t_list	*first;
	t_list	*tmp;

	if (!lst)
		return (0);
	first = funk(lst);
	tmp = first;
	while (lst->next)
	{
		lst = lst->next;
		if (!(tmp->next = funk(lst)))
		{
			free(tmp->next);
			return (0);
		}
		tmp = tmp->next;
	}
	return (first);
}
