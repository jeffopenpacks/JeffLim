/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:30:04 by joolim            #+#    #+#             */
/*   Updated: 2023/10/29 16:45:00 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *str1, char *str2)
{
	char	*tmp;
	size_t	len;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!str1)
	{
		str1 = malloc(1);
		str1[0] = '\0';
	}
	len = ft_strlen_gnl(str1) + ft_strlen_gnl(str2);
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (str1[++i] != '\0')
		tmp[i] = str1[i];
	while (str2[j] != '\0')
		tmp[i++] = str2[j++];
	tmp[i] = '\0';
	free(str1);
	return (tmp);
}

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *str, int c)
{
	char	d;

	d = (char)c;
	if (!str)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == d)
			return (str);
		str++;
	}
	return (NULL);
}
