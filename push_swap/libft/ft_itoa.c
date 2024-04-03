/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:08:01 by joolim            #+#    #+#             */
/*   Updated: 2023/09/22 08:08:01 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len += 1;
	}
	while (n / 10 > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*numstr;
	int			len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = int_len(n);
	numstr = (char *)malloc((len + 1) * sizeof(char));
	if (!numstr)
		return (NULL);
	if (n < 0)
	{
		numstr[0] = '-';
		n = -n;
	}
	if (n == 0)
		numstr[0] = '0';
	numstr[len--] = '\0';
	while (n / 10 > 0)
	{
		numstr[len--] = (n % 10) + '0';
		n /= 10;
	}
	numstr[len] = n + '0';
	return (numstr);
}
