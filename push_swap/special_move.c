/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:51:54 by joolim            #+#    #+#             */
/*   Updated: 2023/11/24 21:28:06 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	special_move_1(t_stack **a, t_stack **b, t_stack *cheapest)
{
	while (*a != cheapest->tgt && b && *b && *b != cheapest)
		rotate(a, b, 'x');
	while (*a != cheapest->tgt)
		rotate(a, b, 'a');
	while (b && *b && *b != cheapest)
		rotate(a, b, 'b');
	push(a, b, 'a');
}

void	special_move_2(t_stack **a, t_stack **b, t_stack *cheapest)
{
	while (*a != cheapest->tgt)
		reverse(a, b, 'a');
	while (b && *b && *b != cheapest)
		rotate(a, b, 'b');
	push(a, b, 'a');
}

void	special_move_3(t_stack **a, t_stack **b, t_stack *cheapest)
{
	while (b && *b && *b != cheapest)
		reverse(a, b, 'b');
	while (*a != cheapest->tgt)
		rotate(a, b, 'a');
	push(a, b, 'a');
}

void	special_move_4(t_stack **a, t_stack **b, t_stack *cheapest)
{
	while (*a != cheapest->tgt && b && *b && *b != cheapest)
		reverse(a, b, 'x');
	while (*a != cheapest->tgt)
		reverse(a, b, 'a');
	while (b && *b && *b != cheapest)
		reverse(a, b, 'b');
	push(a, b, 'a');
}
