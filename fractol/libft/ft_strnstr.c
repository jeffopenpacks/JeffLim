/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:37:05 by joolim            #+#    #+#             */
/*   Updated: 2023/09/20 08:41:40 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	nlen;

	i = 0;
	nlen = ft_strlen(s2);
	if (!s2 || s2[0] == '\0')
		return ((char *)s1);
	while ((*s1 && i < n))
	{
		if (!(ft_strncmp((char *)s1, (char *)s2, nlen)) && (i + nlen) <= n)
			return ((char *)s1);
		s1++;
		i++;
	}
	return (NULL);
}
