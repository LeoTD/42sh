/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:35:21 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/27 17:53:40 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*funk)(t_list *elem))
{
	if (!lst)
		return ;
	funk(lst);
	if (!lst->next)
		return ;
	ft_lstiter(lst->next, funk);
}
