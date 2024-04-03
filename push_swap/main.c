/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:22:29 by joolim            #+#    #+#             */
/*   Updated: 2023/11/27 15:47:13 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	**stacka;
	t_stack	**stackb;
	int		size;
	char	**numarray;

	stacka = NULL;
	stackb = NULL;
	if (argc == 1)
		free_all(NULL, NULL, 2);
	if (argc == 2)
		numarray = ft_split(argv[1], ' ');
	else
		numarray = argv + 1;
	stacka = make_list(stacka);
	stackb = make_list(stackb);
	if (!stacka || !stackb || !numarray)
		free_all(stacka, stackb, -1);
	size = read_stack(stacka, numarray);
	if (check_stack(stacka, stackb) != 0)
		solve4(stacka, stackb, size);
	free_all(stacka, stackb, 1);
	return (0);
}
