/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:18:38 by joolim            #+#    #+#             */
/*   Updated: 2023/11/27 15:20:40 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_px(t_stack **a, t_stack **b)
{
	t_stack	*cur;
	int		sizea;
	int		sizeb;

	sizea = ps_lstsize(*a);
	sizeb = ps_lstsize(*b);
	cur = *b;
	while (cur)
	{
		if (cur->pos <= (sizeb / 2))
		{
			if (cur->tgt->pos <= (sizea / 2))
				cur->px = cur->pos + cur->tgt->pos;
			else
				cur->px = cur->pos + (sizea - cur->tgt->pos + 1);
		}
		else
		{
			if (cur->tgt->pos <= (sizea / 2))
				cur->px = cur->tgt->pos + (sizeb - cur->pos + 1);
			else
				cur->px = (sizea - cur->tgt->pos + 1) + (sizeb - cur->pos + 1);
		}
		cur = cur->next;
	}
}

void	set_tgt(t_stack **a, t_stack **b)
{
	t_stack	*current;
	t_stack	*tgt;
	t_stack	*pot;

	current = *b;
	while (current)
	{
		tgt = *a;
		pot = NULL;
		while (tgt)
		{
			if (tgt->content > current->content)
				if (!pot || (pot && pot->content > tgt->content))
					pot = tgt;
			tgt = tgt->next;
		}
		if (pot == NULL)
			current->tgt = smollest(a);
		else
			current->tgt = pot;
		current = current->next;
	}
	set_px(a, b);
}

static t_stack	*find_cheapest(t_stack **b)
{
	t_stack	*current;
	t_stack	*cheapest;

	current = *b;
	cheapest = current;
	while (current)
	{
		if (cheapest->px > current->px)
			cheapest = current;
		current = current->next;
	}
	return (cheapest);
}

static void	move_cheapest(t_stack **a, t_stack **b)
{
	t_stack	*cheapest;

	while (b && *b)
	{
		cheapest = find_cheapest(b);
		if (cheapest->pos < (ps_lstsize(*b) / 2))
		{
			if (cheapest->tgt->pos < (ps_lstsize(*a) / 2))
				special_move_1(a, b, cheapest);
			else
				special_move_2(a, b, cheapest);
		}
		else
		{
			if (cheapest->tgt->pos < (ps_lstsize(*a) / 2))
				special_move_3(a, b, cheapest);
			else
				special_move_4(a, b, cheapest);
		}
	}
}

int	solve4(t_stack **a, t_stack **b, int size)
{
	if (size <= 5)
		sort_three(a, b);
	else
	{
		while (size > 3)
		{
			elegant_push(a, b);
			size--;
		}
		sort_three(a, b);
		move_cheapest(a, b);
		while (*a != smollest(a))
		{
			if (smollest(a)->pos < (size / 2))
				rotate(a, b, 'a');
			else
				reverse(a, b, 'a');
		}
	}
	return (1);
}
