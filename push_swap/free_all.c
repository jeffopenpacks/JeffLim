/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:36:24 by joolim            #+#    #+#             */
/*   Updated: 2023/11/27 15:08:32 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_all(t_stack **a, t_stack **b, int flag)
{
	if (a != NULL)
	{
		ps_lstclear(a, &free);
		free(a);
		a = NULL;
	}
	if (b != NULL)
	{
		ps_lstclear(b, &free);
		free(b);
		b = NULL;
	}
	if (flag < 0)
	{
		write(2, "ERROR\n", 6);
		exit(1);
	}
	if (flag == 2)
	{
		write(2, "No parameters specified", 23);
		exit(0);
	}
}
