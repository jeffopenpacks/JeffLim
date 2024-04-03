/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:53:56 by joolim            #+#    #+#             */
/*   Updated: 2023/09/18 17:55:02 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char			*destptr;
	const unsigned char		*srcptr;

	if (!dest && !src)
		return (0);
	destptr = (unsigned char *)dest;
	srcptr = (const unsigned char *)src;
	while (len--)
	{
		*destptr = *srcptr;
		destptr++;
		srcptr++;
	}
	return (dest);
}
