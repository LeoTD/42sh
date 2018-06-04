/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:44:11 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/27 16:54:23 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** The recursive version: (Opted for iterative out of concerns for memory usage)
**
**	if ((*lst)->next)
**		ft_lstdel(&(*lst)->next, del);
**	ft_lstdelone(&(*lst), del);
*/

void	ft_lstdel(t_list **lst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*prev;

	if (!lst || !*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		ft_lstdelone(&prev, del);
	}
	*lst = 0;
}
