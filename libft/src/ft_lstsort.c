/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 20:29:24 by ltanenba          #+#    #+#             */
/*   Updated: 2018/05/03 21:46:47 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Comparison function returns [ 1 ] if [ a ] takes precedence.
** and [ 0 ] if [ b ].
*/

static void		st_split(t_list *head, t_list **a, t_list **b)
{
	t_list	*fast;
	t_list	*slow;

	if (head == NULL || head->next == NULL)
	{
		*a = head;
		*b = NULL;
		return ;
	}
	slow = head;
	fast = head->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = head;
	*b = slow->next;
	slow->next = NULL;
}

static t_list	*st_merge(t_list *a, t_list *b, int (*cmp)(void *, void *))
{
	t_list	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (cmp(a->content, b->content))
	{
		result = a;
		result->next = st_merge(a->next, b, cmp);
	}
	else
	{
		result = b;
		result->next = st_merge(a, b->next, cmp);
	}
	return (result);
}

void			ft_lstsort(t_list **head, int (*cmp)(void *, void *))
{
	t_list	*a;
	t_list	*b;
	t_list	*first;

	first = *head;
	if (first == NULL || first->next == NULL)
		return ;
	st_split(first, &a, &b);
	ft_lstsort(&a, cmp);
	ft_lstsort(&b, cmp);
	*head = st_merge(a, b, cmp);
}
