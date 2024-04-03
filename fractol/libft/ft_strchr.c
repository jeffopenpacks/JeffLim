/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:48:02 by joolim            #+#    #+#             */
/*   Updated: 2023/09/20 12:04:38 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int character)
{
	while (*str)
	{
		if (*str == (unsigned char)character)
			return ((char *)str);
		str++;
	}
	if ((unsigned char)character == '\0')
		return ((char *)str);
	return (NULL);
}
