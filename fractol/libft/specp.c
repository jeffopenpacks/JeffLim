/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:07:26 by joolim            #+#    #+#             */
/*   Updated: 2023/10/29 14:39:56 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	puthexul(unsigned long n, const char *base)
{
	int	len;

	len = 0;
	if (n > 15)
	{
		len += puthexul(n / 16, base);
		len += specc(base[n % 16]);
	}
	else
		len += specc(base[n % 16]);
	return (len);
}

int	specp(void *ptr)
{
	int				len;
	unsigned long	n;

	n = (unsigned long)ptr;
	len = 0;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	(void)specs("0x");
	len += 2;
	len += puthexul(n, "0123456789abcdef");
	return (len);
}
