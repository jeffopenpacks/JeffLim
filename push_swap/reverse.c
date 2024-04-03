/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:26:27 by joolim            #+#    #+#             */
/*   Updated: 2023/11/27 18:37:30 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	reverse_node(t_stack **stack)
{
	int		size;
	t_stack	*tmp;
	t_stack	*newtail;

	tmp = *stack;
	size = ps_lstsize(*stack);
	if (size <= 1)
		return (0);
	while (size > 2)
	{
		tmp = tmp->next;
		size--;
	}
	newtail = tmp;
	ps_lstadd_front(stack, tmp->next);
	newtail->next = NULL;
	return (1);
}

int	reverse(t_stack **stacka, t_stack **stackb, char c)
{
	if (c == 'a')
	{
		if (reverse_node(stacka) != 0)
			ft_printf("rra\n");
	}
	else if (c == 'b')
	{
		if (reverse_node(stackb) != 0)
			ft_printf("rrb\n");
	}
	else if (c == 'x')
	{
		if (reverse_node(stacka) != 0 && reverse_node(stackb) != 0)
			ft_printf("rrr\n");
	}
	else if (c == 'z')
	{
		reverse_node(stacka);
		reverse_node(stackb);
	}
	update_pos(stacka, stackb);
	return (0);
}
