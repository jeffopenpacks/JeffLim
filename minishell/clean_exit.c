/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:54:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/07/15 12:54:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir_jl(t_data *data, int inst_num)
{
	int	i;

	i = 0;
	while (data->inst[inst_num]->redir[i])
	{
		free(data->inst[inst_num]->redir[i]->str);
		free(data->inst[inst_num]->redir[i]);
		i++;
	}
	free(data->inst[inst_num]->redir);
}

void	free_inst_jl(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->inst[i])
	{
		if (data->inst[i]->redir)
			free_redir_jl(data, i);
		j = 0;
		if (data->inst[i]->arr)
		{
			while (data->inst[i]->arr[j])
			{
				free(data->inst[i]->arr[j]);
				j++;
			}
			free(data->inst[i]->arr);
		}
		if (data->inst[i]->str)
			free(data->inst[i]->str);
		free(data->inst[i]);
		i++;
	}
	free(data->inst);
}

void	clean_exit(t_data *data)
{
	free_inst_jl(data);
	free_environ(data->environ);
}
