/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_delink.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 04:02:41 by ltanenba          #+#    #+#             */
/*   Updated: 2018/03/30 21:33:55 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delinklr(t_clist *n)
{
	(n->left)->right = n->left;
	(n->right)->left = n->right;
}

void	ft_delinkud(t_clist *n)
{
	(n->up)->down = n->up;
	(n->down)->up = n->down;
}
