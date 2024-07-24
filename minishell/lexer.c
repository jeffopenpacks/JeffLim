/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:07:22 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 14:48:19 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_chars(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_strchr("<>|", input[i]) != 0 || ft_isspace(input[i]) != 0)
			return (i);
		else if (ft_strchr("'\"", input[i]) == 0)
			i++;
		else if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				i++;
			i++;
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i] != '"')
				i++;
			i++;
		}
	}
	return (i);
}

static int	count_tokens(const char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < ft_strlen(input))
	{
		if (ft_isspace(input[i]) != 0)
			i++;
		else if (ft_strchr("<>|", input[i]) != 0)
		{
			count++;
			if (ft_strchr("<>", input[i]) != 0 && input[i] == input[i + 1])
				i += 2;
			else
				i++;
		}
		else
		{
			count++;
			i += count_chars(&input[i]);
		}
	}
	return (count);
}

static void	find_tokens2(char *input, t_data *data, t_token **tokens, int j)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]) != 0)
			i++;
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i += make_tokens(&input[i], tokens[j++], i, 3);
		else
			i += make_tokens(&input[i], tokens[j++], i, 4);
	}
	tokens[j] = NULL;
	data->tokens = tokens;
}

void	find_tokens(char *input, t_data *data)
{
	int		i;
	int		j;
	t_token	**tokens;

	i = 0;
	j = 0;
	j = count_tokens(input);
	tokens = (t_token **)malloc((j + 1) * sizeof(t_token *));
	safe_fn(tokens, data);
	while (i < j)
	{
		tokens[i] = (t_token *)malloc(sizeof(t_token));
		safe_fn(tokens[i], data);
		tokens[i]->str = NULL;
		tokens[i]->data = data;
		i++;
	}
	find_tokens2(input, data, tokens, 0);
}
