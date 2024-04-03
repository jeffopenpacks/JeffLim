/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:58:20 by joolim            #+#    #+#             */
/*   Updated: 2023/09/20 13:20:16 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *a, const void *b, size_t len)
{
	unsigned int			i;
	const unsigned char		*ptra;
	const unsigned char		*ptrb;

	i = 0;
	ptra = (const unsigned char *)a;
	ptrb = (const unsigned char *)b;
	if (ptra == ptrb || len == 0)
		return (0);
	while (*ptra == *ptrb && i < (len - 1))
	{
		ptra++;
		ptrb++;
		i++;
	}
	return (*ptra - *ptrb);
}
