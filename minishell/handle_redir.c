/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:53:26 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 13:53:27 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_type(t_data *data, int i, int j, int k)
{
	if (data->tokens[i]->str[0] == '<')
	{
		if (ft_strlen(data->tokens[i]->str) == 2)
			data->inst[k]->redir[j]->type = 1;
		else
			data->inst[k]->redir[j]->type = 2;
	}
	else
	{
		if (ft_strlen(data->tokens[i]->str) == 2)
			data->inst[k]->redir[j]->type = 3;
		else
			data->inst[k]->redir[j]->type = 4;
	}
}

static void	handle_redir3(t_data *data, int j, int i, int k)
{
	while (data->tokens[i] && data->tokens[i]->str[0] != '|')
	{
		if (data->tokens[i]->str[0] == '<' || data->tokens[i]->str[0] == '>')
		{
			data->inst[k]->redir[j] = (t_redir *)malloc(sizeof(t_redir));
			safe_fn(data->inst[k]->redir[j], data);
			assign_type(data, i, j, k);
			data->inst[k]->redir[j]->str = \
				ft_rddup(data->tokens[i + 1]->str, data);
			pop_token(data, i);
			pop_token(data, i);
			j++;
		}
		else
			i++;
	}
	data->inst[k]->redir[j] = NULL;
}

static void	handle_redir2(t_data *data, int j)
{
	int	i;
	int	k;

	i = 0;
	k = j;
	while (j != 0)
	{
		if (data->tokens[i++]->str[0] == '|')
			j--;
	}
	handle_redir3(data, j, i, k);
}

static void	assign_redir(t_data *data, int count, int k)
{
	data->inst[k]->redir = (t_redir **)malloc((count + 1) * sizeof(t_redir *));
	safe_fn(data->inst[k]->redir, data);
	data->inst[k]->redir[count] = NULL;
	handle_redir2(data, k);
}

t_redir	**handle_redir(t_data *data, int j, int count)
{
	int	i;
	int	k;

	k = j;
	i = 0;
	while (j != 0)
	{
		if (data->tokens[i++]->str[0] == '|')
			j--;
	}
	while (data->tokens[i] && data->tokens[i]->str[0] != '|')
	{
		if (ft_strchr("<>", data->tokens[i]->str[0]) != 0)
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	if (count == 0)
		return (NULL);
	else
		assign_redir(data, count, k);
	return (data->inst[k]->redir);
}
