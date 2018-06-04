/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_lstcadd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 04:05:12 by ltanenba          #+#    #+#             */
/*   Updated: 2018/03/30 21:34:08 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstcaddr(t_clist *lst, t_clist *n)
{
	n->left = lst;
	n->right = lst->right;
	ft_relinklr(n);
}

void	ft_lstcaddl(t_clist *lst, t_clist *n)
{
	n->left = lst->left;
	n->right = lst;
	ft_relinklr(n);
}

void	ft_lstcaddu(t_clist *lst, t_clist *n)
{
	n->up = lst->up;
	n->down = lst;
	ft_relinkud(n);
}

void	ft_lstcaddd(t_clist *lst, t_clist *n)
{
	n->down = lst->down;
	n->up = lst;
	ft_relinkud(n);
}
