/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:07:13 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 14:50:23 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_len2(char *str)
{
	int	j;

	j = 0;
	if ((str[j] == '<' || str[j] == '>') && (str[j] == str[j + 1]))
		j = 2;
	else
		j = 1;
	return (j);
}

static int	find_len1(char *str)
{
	int	j;

	j = 0;
	while (j < ft_strlen(str))
	{
		if (ft_strchr("<>|", str[j]) != 0 || ft_isspace(str[j]) != 0)
			return (j);
		if (str[j] == '\'' || str[j] == '"')
		{
			j++;
			if (str[j - 1] == '\'')
			{
				while (str[j] != '\'')
					j++;
			}
			else
			{
				while (str[j] != '"')
					j++;
			}
		}
		j++;
	}
	return (j);
}

int	make_tokens(char *str, t_token *tokens, int pos, int option)
{
	int	len;

	len = 0;
	tokens->pos = pos;
	if (option == 3)
		len = find_len2(str);
	if (option == 4)
		len = find_len1(str);
	tokens->str = (char *)malloc(len + 1);
	safe_fn(tokens->str, tokens->data);
	ft_strlcpy(tokens->str, str, len + 1);
	return (len);
}
