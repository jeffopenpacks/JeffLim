/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:30:42 by joolim            #+#    #+#             */
/*   Updated: 2023/11/27 18:53:03 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	perform_move(t_stack **a, t_stack **b, char *str)
{
	if (ft_strnstr(str, "sa\n", 3))
		swap_node(a);
	else if (ft_strnstr(str, "sb\n", 3))
		swap_node(b);
	else if (ft_strnstr(str, "ss\n", 3))
		swap(a, b, 'z');
	else if (ft_strnstr(str, "pa\n", 3))
		push_node(a, b);
	else if (ft_strnstr(str, "pb\n", 3))
		push_node(b, a);
	else if (ft_strnstr(str, "ra\n", 3))
		rotate_node(a);
	else if (ft_strnstr(str, "rb\n", 3))
		rotate_node(b);
	else if (ft_strnstr(str, "rr\n", 3))
		rotate(a, b, 'z');
	else if (ft_strnstr(str, "rra\n", 4))
		reverse_node(a);
	else if (ft_strnstr(str, "rrb\n", 4))
		reverse_node(b);
	else if (ft_strnstr(str, "rrr\n", 4))
		reverse(a, b, 'z');
	else
		return (-1);
	return (0);
}

static void	check_moves(t_stack **a, t_stack **b)
{
	char	*str;
	int		move;

	move = 0;
	while (1)
	{
		str = get_next_line(0);
		if (!str)
			break ;
		move += perform_move(a, b, str);
		free(str);
		if (move == -1)
		{
			write(2, "Error\n", 6);
			break ;
		}
	}
	if (move == 0)
	{
		if (check_stack(a, b) == 0)
			ft_printf("OK\n");
		else
			ft_printf("KO\n");
	}
}

int	main(int argc, char **argv)
{
	t_stack	**stacka;
	t_stack	**stackb;
	char	**numarray;

	stacka = NULL;
	stackb = NULL;
	if (argc == 1)
		exit(0);
	if (argc == 2)
		numarray = ft_split(argv[1], ' ');
	else
		numarray = argv + 1;
	stacka = make_list(stacka);
	stackb = make_list(stackb);
	read_stack(stacka, numarray);
	if (argc == 2)
		free(numarray);
	check_moves(stacka, stackb);
	free_all(stacka, stackb, 0);
	return (1);
}
