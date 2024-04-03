/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:22:41 by joolim            #+#    #+#             */
/*   Updated: 2023/11/24 19:44:47 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_lstadd_front(t_stack **lst, t_stack *new)
{
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

void	ps_lstclear(t_stack **lst, void (*del)(void*))
{
	t_stack		*holdlist;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		holdlist = (*lst)->next;
		free(*lst);
		*lst = holdlist;
	}
	*lst = NULL;
}

int	ps_lstsize(t_stack *lst)
{
	size_t	len;

	len = 0;
	while (lst != NULL)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void	ps_lstadd_back(t_stack **lst, t_stack *new)
{
	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
			ps_lstlast(*lst)->next = new;
	}
}

t_stack	*ps_lstlast(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
