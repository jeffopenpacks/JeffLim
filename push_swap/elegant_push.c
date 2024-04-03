/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elegant_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:24:11 by joolim            #+#    #+#             */
/*   Updated: 2023/11/24 21:08:25 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_mid(t_stack *cur, t_stack **a)
{
	int		smol;
	int		lrg;
	t_stack	*current;

	current = *a;
	smol = 0;
	lrg = 0;
	while (current != NULL)
	{
		if (cur->content == current->content)
		{
			current = current->next;
			continue ;
		}
		else if (cur->content < current->content)
			lrg++;
		else if (cur->content > current->content)
			smol++;
		current = current->next;
	}
	if (ps_lstsize(*a) % 2 == 0)
		return (lrg == smol + 1 || lrg + 1 == smol);
	else if (ps_lstsize(*a) % 2 != 0)
		return (lrg == smol);
	return (0);
}

static int	mid_value(t_stack **a)
{
	t_stack	*current;

	current = *a;
	while (current != NULL)
	{
		if (find_mid(current, a) == 1)
			return (current->content);
		current = current->next;
	}
	return (0);
}

int	elegant_push(t_stack **a, t_stack **b)
{
	if ((*a)->content < mid_value(a))
		push(a, b, 'b');
	else
	{
		push(a, b, 'b');
		rotate(a, b, 'b');
	}
	return (0);
}
