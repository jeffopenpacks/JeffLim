/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:52:31 by joolim            #+#    #+#             */
/*   Updated: 2023/09/20 12:26:55 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	negcheck(char c)
{
	if (c == '+')
		return (1);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	negcounter;
	int	result;

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
		return (result *= negcounter);
	}
	return (0);
}
