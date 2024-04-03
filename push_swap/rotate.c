/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:17:55 by joolim            #+#    #+#             */
/*   Updated: 2023/11/27 18:36:30 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rotate_node(t_stack **stack)
{
	t_stack	*tmp;

	if (!(*stack) || ps_lstsize(*stack) < 2)
		return (0);
	tmp = *stack;
	*stack = (*stack)->next;
	ps_lstadd_back(stack, tmp);
	tmp->next = NULL;
	return (1);
}

int	rotate(t_stack **stacka, t_stack **stackb, char c)
{
	if (c == 'a')
	{
		if (rotate_node(stacka) != 0)
			ft_printf("ra\n");
	}
	else if (c == 'b')
	{
		if (rotate_node(stackb) != 0)
			ft_printf("rb\n");
	}
	else if (c == 'x')
	{
		if (rotate_node(stacka) != 0 && rotate_node(stackb) != 0)
			ft_printf("rr\n");
	}
	else if (c == 'z')
	{
		rotate_node(stacka);
		rotate_node(stackb);
	}
	update_pos(stacka, stackb);
	return (0);
}
