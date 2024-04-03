/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:35:33 by joolim            #+#    #+#             */
/*   Updated: 2023/09/20 12:46:44 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int character)
{
	unsigned int	i;

	i = 0;
	i = ft_strlen(str);
	while (str[i] != (unsigned char)character)
	{
		if (i <= 0)
			return (NULL);
		i--;
	}
	return ((char *)(str + i));
}
