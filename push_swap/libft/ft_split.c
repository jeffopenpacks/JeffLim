/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 07:47:45 by joolim            #+#    #+#             */
/*   Updated: 2023/09/22 09:27:51 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	word;
	int	count;

	i = 0;
	count = 0;
	word = 0;
	while (s[i])
	{
		if (word == 0 && s[i] != c)
		{
			count++;
			word = 1;
		}
		if (word == 1 && s[i] == c)
			word = 0;
		i++;
	}
	return (count);
}

static int	make_word(char **strarr, char *str, char set)
{
	int	len;
	int	i;

	len = 0;
	while (str[len] && str[len] != set)
		len++;
	*strarr = malloc(sizeof(char) * (len + 1));
	if (!*strarr)
		return (0);
	i = 0;
	while (i < len)
	{
		strarr[0][i] = str[i];
		i++;
	}
	strarr[0][i] = '\0';
	return (1);
}

static char	**free_split(char **strs, int i)
{
	while (i >= 0)
		free(strs[i--]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strarr;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)s;
	strarr = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!strarr)
		return (NULL);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && !make_word(&strarr[i++], str, c))
			return (free_split(strarr, i));
		while (*str && *str != c)
			str++;
	}
	strarr[i] = NULL;
	return (strarr);
}
