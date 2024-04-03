/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:26:24 by joolim            #+#    #+#             */
/*   Updated: 2023/11/25 15:24:59 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*largest(t_stack **stacka)
{
	t_stack	*current;
	t_stack	*largest;

	current = *stacka;
	largest = current;
	while (current)
	{
		if (largest->content < current->content)
			largest = current;
		current = current->next;
	}
	return (largest);
}

t_stack	*smollest(t_stack **stacka)
{
	t_stack		*current;
	t_stack		*smollest;

	current = *stacka;
	smollest = current;
	while (current)
	{
		if (smollest->content > current->content)
			smollest = current;
		current = current->next;
	}
	return (smollest);
}

static int	handle_2(t_stack **a, t_stack **b)
{
	int	size;

	size = ps_lstsize(*a);
	if (size == 1)
		return (1);
	else if ((*a)->content < (*a)->next->content)
		return (1);
	else
		swap(a, b, 'a');
	return (1);
}

static int	sort_five(t_stack **a, t_stack **b)
{
	while (ps_lstsize(*a) > 3)
	{
		while (*a != smollest(a))
		{
			if (smollest(a)->pos > 3)
				reverse(a, b, 'a');
			else
				rotate(a, b, 'a');
		}
		push(a, b, 'b');
	}
	sort_three(a, b);
	if (ps_lstsize(*b) == 2 && ((*b)->content < (*b)->next->content))
		swap(a, b, 'b');
	while (b && *b)
		push(a, b, 'a');
	return (1);
}

int	sort_three(t_stack **a, t_stack **b)
{
	if (ps_lstsize(*a) > 3)
		return (sort_five(a, b));
	if (ps_lstsize(*a) < 3)
		return (handle_2(a, b));
	if ((*a)->next->next->content != largest(a)->content)
	{
		if ((*a)->content == largest(a)->content)
			rotate(a, b, 'a');
		else if ((*a)->next->content == largest(a)->content)
			reverse(a, b, 'a');
	}
	if ((*a)->next->content < (*a)->content)
		swap(a, b, 'a');
	return (1);
}
