/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:53:46 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 13:53:48 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_rddup(char *str, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			tmp = (char *)safe_fn(ft_strjoin_char(tmp, str[i]), data);
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				tmp = (char *)safe_fn(ft_strjoin_char(tmp, str[i++]), data);
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				tmp = (char *)safe_fn(ft_strjoin_char(tmp, str[i++]), data);
		}
		i++;
	}
	return (tmp);
}

static void	make_empty_buf(t_inst *inst, char *str)
{
	char	**buf;

	buf = (char **)malloc(2 * sizeof(char *));
	safe_fn(buf, inst->data);
	buf[0] = (char *)safe_fn(ft_strdup(str), inst->data);
	buf[1] = NULL;
	inst->arr = buf;
	return ;
}

static void	ft_arrappend(t_inst *inst, char *str, t_data *data, int count)
{
	char	**buf;

	if (!inst->arr)
		return (make_empty_buf(inst, str));
	else
	{
		while (inst->arr[count] != NULL)
			count++;
	}
	buf = (char **)malloc((count + 2) * sizeof(char *));
	safe_fn(buf, data);
	count = 0;
	while (inst->arr[count])
	{
		buf[count] = (char *)safe_fn(ft_strdup(inst->arr[count]), data);
		free(inst->arr[count]);
		inst->arr[count] = NULL;
		count++;
	}
	free(inst->arr);
	inst->arr = NULL;
	buf[count] = (char *)safe_fn(ft_strdup(str), data);
	buf[count + 1] = NULL;
	inst->arr = buf;
}

static void	populate_inst(t_data *data, int i, int j)
{
	while (data->tokens[i])
	{
		if (data->tokens[i]->str[0] == '|')
		{
			pop_token(data, i);
			j++;
			continue ;
		}
		if (!data->tokens[i])
			break ;
		if (!data->inst[j]->arr)
		{
			data->inst[j]->arr = (char **)malloc(sizeof(char *));
			safe_fn(data->inst[j]->arr, data);
			data->inst[j]->arr[0] = NULL;
		}
		if (data->tokens[i])
		{
			remove_quotes(data->tokens[i], 0);
			ft_arrappend(data->inst[j], data->tokens[i]->str, data, 0);
		}
		i++;
	}
}

void	init_inst(t_data *data, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		data->inst[j] = (t_inst *)malloc(sizeof(t_inst));
		safe_fn(data->inst[j], data);
		data->inst[j]->redir = handle_redir(data, j, 0);
		data->inst[j]->data = data;
		data->inst[j]->arr = NULL;
		data->inst[j]->str = NULL;
		j++;
	}
	populate_inst(data, 0, 0);
}
