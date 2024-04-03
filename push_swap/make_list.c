/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:40:56 by joolim            #+#    #+#             */
/*   Updated: 2023/11/27 18:57:26 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_stack(t_stack **a, t_stack **b)
{
	int		res_b;
	int		res_a;
	t_stack	*current;

	res_b = ps_lstsize(*b);
	res_a = 0;
	current = *a;
	while (current->next)
	{
		if (current->content < current->next->content)
			current = current->next;
		else
		{
			res_a = 1;
			break ;
		}
	}
	if (res_a + res_b == 0)
		return (0);
	else
		return (-1);
}

void	update_pos(t_stack **a, t_stack **b)
{
	t_stack	*current;
	int		pos;

	current = *a;
	pos = 1;
	while (current)
	{
		current->pos = pos;
		pos++;
		current = current->next;
	}
	if (b && *b)
	{
		current = *b;
		pos = 1;
		while (current)
		{
			current->pos = pos;
			pos++;
			current = current->next;
		}
		set_tgt(a, b);
	}
}

t_stack	**make_list(t_stack **lst)
{
	t_stack	**stacka;

	stacka = (t_stack **)malloc(sizeof(t_stack *));
	if (!stacka)
		return (NULL);
	*stacka = NULL;
	lst = stacka;
	return (lst);
}

t_stack	*add_node(t_stack **lst)
{
	t_stack	*newnode;

	newnode = (t_stack *)malloc(sizeof(t_stack));
	if (!newnode)
		free_all(lst, NULL, -1);
	newnode->content = 0;
	newnode->next = NULL;
	newnode->tgt = NULL;
	newnode->px = 0;
	newnode->pos = 0;
	ps_lstadd_back(lst, newnode);
	update_pos(lst, NULL);
	return (newnode);
}

int	read_stack(t_stack **lst, char **numarray)
{
	t_stack	*current;
	int		i;

	current = add_node(lst);
	*lst = current;
	i = 0;
	check_data(lst, numarray);
	while (numarray[i] != NULL)
	{
		current->content = convert_int(lst, numarray[i]);
		if (numarray[i + 1] != NULL)
		{
			current->next = add_node(lst);
			current = current->next;
		}
		i++;
	}
	check_dup(lst);
	return (ps_lstsize(*lst));
}
