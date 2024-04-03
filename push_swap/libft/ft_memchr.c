/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:20:07 by joolim            #+#    #+#             */
/*   Updated: 2023/09/20 13:10:46 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	char			*sptr;
	char			character;

	i = 0;
	sptr = (char *)s;
	character = (char)c;
	while (i < n)
	{
		if (*sptr == character)
			return (sptr);
		sptr++;
		i++;
	}
	return (NULL);
}
