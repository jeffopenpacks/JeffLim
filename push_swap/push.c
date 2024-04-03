/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:54:00 by joolim            #+#    #+#             */
/*   Updated: 2023/11/27 13:34:43 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_node(t_stack **stack1, t_stack **stack2)
{
	t_stack	*tmp;

	if (!(*stack2))
		return (0);
	tmp = *stack2;
	*stack2 = (*stack2)->next;
	tmp->next = *stack1;
	*stack1 = tmp;
	return (1);
}

int	push(t_stack **stacka, t_stack **stackb, char c)
{
	int	flag1;

	flag1 = 0;
	if (c == 'a')
	{
		flag1 = push_node(stacka, stackb);
		if (flag1)
			ft_printf("pa\n");
	}
	else if (c == 'b')
	{
		flag1 = push_node(stackb, stacka);
		if (flag1)
			ft_printf("pb\n");
	}
	update_pos(stacka, stackb);
	return (0);
}
