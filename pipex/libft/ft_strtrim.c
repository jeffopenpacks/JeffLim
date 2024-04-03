/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:23:44 by joolim            #+#    #+#             */
/*   Updated: 2023/09/21 16:59:57 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	int		start;
	char	*newstr;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	while (s1[i] && isset(s1[i], set))
		i++;
	j = len - 1;
	while (j >= i && isset(s1[j], set))
		j--;
	newstr = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!newstr)
		return (NULL);
	start = 0;
	while (s1[i] && i <= j)
		newstr[start++] = s1[i++];
	newstr[start] = '\0';
	return (newstr);
}
