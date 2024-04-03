/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:50:20 by joolim            #+#    #+#             */
/*   Updated: 2023/09/14 18:05:16 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t		i;
	char		*destptr;
	char		*srcptr;

	destptr = (char *)dest;
	srcptr = (char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (destptr > srcptr)
	{
		while (len-- > 0)
			destptr[len] = srcptr[len];
	}
	else
	{
		while (i < len)
		{
			destptr[i] = srcptr[i];
			i++;
		}
	}
	return (dest);
}
