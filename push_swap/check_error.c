/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:11:53 by joolim            #+#    #+#             */
/*   Updated: 2023/11/26 13:23:19 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	negcheck(char c)
{
	if (c == '+')
		return (1);
	else
		return (-1);
}

static long	ft_atol(const char *str)
{
	int		i;
	long	negcounter;
	long	result;

	i = 0;
	result = 0;
	negcounter = 1;
	while (str[i])
	{
		while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
			i++;
		if (str[i] == 45 || str[i] == 43)
		{
			negcounter *= negcheck(str[i]);
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			result = (result * 10) + (str[i] - '0');
			i++;
		}
	}
	return (result *= negcounter);
}

int	check_data(t_stack **lst, char **numarray)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (numarray[i])
	{
		if (numarray[i][j] == '-')
			j = 1;
		while (numarray[i][j])
		{
			if (!(numarray[i][j] >= '0' && numarray[i][j] <= '9'))
				free_all(lst, NULL, -1);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	check_dup(t_stack **lst)
{
	t_stack	*current;
	t_stack	*compare;

	current = *lst;
	compare = current->next;
	while (current)
	{
		compare = current->next;
		while (compare)
		{
			if (current->content == compare->content)
				free_all(lst, NULL, -1);
			compare = compare->next;
		}
		current = current->next;
	}
	return (1);
}

int	convert_int(t_stack **lst, char *numstr)
{
	long	tmp;

	tmp = ft_atol(numstr);
	if (tmp > INT_MAX || tmp < INT_MIN)
		free_all(lst, NULL, -1);
	return ((int)tmp);
}
