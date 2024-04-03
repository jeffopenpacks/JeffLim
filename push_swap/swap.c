/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:24:26 by joolim            #+#    #+#             */
/*   Updated: 2023/11/27 18:37:03 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	swap_node(t_stack **stacka)
{
	t_stack	*tmp;

	if (stacka == NULL || (*stacka)->next == NULL)
		return (0);
	tmp = (*stacka)->next;
	(*stacka)->next = tmp->next;
	tmp->next = *stacka;
	*stacka = tmp;
	return (1);
}

int	swap(t_stack **stacka, t_stack **stackb, char c)
{
	if (c == 'a')
	{
		if (swap_node(stacka) != 0)
			ft_printf("sa\n");
	}
	else if (c == 'b')
	{
		if (swap_node(stackb) != 0)
			ft_printf("sb\n");
	}
	else if (c == 'x')
	{
		if (swap_node(stacka) != 0 && swap_node(stackb) != 0)
			ft_printf("ss\n");
	}
	else if (c == 'z')
	{
		swap_node(stacka);
		swap_node(stackb);
	}
	update_pos(stacka, stackb);
	return (0);
}
