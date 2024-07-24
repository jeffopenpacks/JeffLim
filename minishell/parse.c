/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:33:12 by joolim            #+#    #+#             */
/*   Updated: 2024/07/12 11:39:05 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ret_empty(t_token *token)
{
	char	*tmp;

	tmp = malloc(1);
	if (!tmp)
		return ;
	tmp[0] = '\0';
	free(token->str);
	token->str = tmp;
}

static int	token_check(t_token *token)
{
	if (ft_strlen(token->str) == 2 && ft_strchr("\"'", token->str[0]) != NULL \
			&& token->str[0] == token->str[1])
	{
		ret_empty(token);
		return (1);
	}
	if (ft_strchr(token->str, '\'') == 0 && ft_strchr(token->str, '"') == 0)
		return (1);
	return (0);
}

void	remove_quotes(t_token *token, int i)
{
	char	*tmp;

	tmp = NULL;
	if (token_check(token) == 1)
		return ;
	while (token->str[i])
	{
		if (token->str[i] != '\'' && token->str[i] != '"')
			tmp = ft_strjoin_char(tmp, token->str[i]);
		else if (token->str[i] == '\'')
		{
			i++;
			while (token->str[i] != '\'')
				tmp = ft_strjoin_char(tmp, token->str[i++]);
		}
		else if (token->str[i] == '"')
		{
			i++;
			while (token->str[i] != '"')
				tmp = ft_strjoin_char(tmp, token->str[i++]);
		}
		i++;
	}
	free(token->str);
	token->str = tmp;
}

static int	pre_parse(t_data *data, int i)
{
	while (data->tokens[i])
	{
		if (ft_strlen(data->tokens[i]->str) == 0)
		{
			pop_token(data, i);
			continue ;
		}
		if ((ft_strchr("<>", data->tokens[i]->str[0]) != 0 \
					&& (!data->tokens[i + 1] \
						|| ft_strchr("<>|", data->tokens[i + 1]->str[0]))) \
				|| (data->tokens[i]->str[0] == '|' && (!data->tokens[i + 1] \
						|| data->tokens[i + 1]->str[0] == '|')))
		{
			printf("Syntax error\n");
			data->exit_status = 2;
			return (2);
		}
		else
			i++;
	}
	return (0);
}

int	parse(t_data *data)
{
	int	size;
	int	i;

	size = 1;
	i = 0;
	dolla(data->tokens);
	if (pre_parse(data, 0) != 0)
		return (2);
	while (data->tokens[i])
	{
		if ((ft_strlen(data->tokens[i]->str) == 1) \
				&& data->tokens[i]->str[0] == '|')
			size++;
		i++;
	}
	data->inst = (t_inst **)malloc((size + 1) * sizeof(t_inst *));
	safe_fn(data->inst, data);
	data->inst[size] = NULL;
	init_inst(data, size);
	return (0);
}
