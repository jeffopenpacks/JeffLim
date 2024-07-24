/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:52:33 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 14:53:22 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_char_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

static void	free_redir(t_redir **redir)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (redir[i]->str)
			free(redir[i]->str);
		free(redir[i]);
		i++;
	}
	free(redir);
	redir = NULL;
}

void	free_inst(t_data *data)
{
	int	i;

	i = 0;
	while (data->inst[i])
	{
		if (data->inst[i]->redir)
			free_redir(data->inst[i]->redir);
		if (data->inst[i]->arr)
			free_char_arr(data->inst[i]->arr);
		if (data->inst[i]->str)
			free(data->inst[i]->str);
		free(data->inst[i]);
		i++;
	}
	free(data->inst);
}

void	free_tokens(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		if (data->tokens[i]->str)
			free(data->tokens[i]->str);
		free(data->tokens[i]);
		i++;
	}
	free(data->tokens);
}

/*void	jl_test_print(t_data *data)
{
	for(int i = 0; data->inst[i]; i++)
	{
		printf("inst[%i]:\n", i);
		for(int j = 0; data->inst[i]->arr[j]; j++)
			printf("\tarr[%i]: %s\n", j, data->inst[i]->arr[j]);
		if (data->inst[i]->redir)
		{
			for(int k = 0; data->inst[i]->redir[k]; k++)
			{
				printf("\tredir[%i]:\n", k);
				printf("\t\ttype: %i\n", data->inst[i]->redir[k]->type);
				printf("\t\tstr: %s\n", data->inst[i]->redir[k]->str);
			}
		}
	}
}*/

int	process(char *input, t_data *data)
{
	int	status;

	status = 0;
	find_tokens(input, data);
	status = parse(data);
	free_tokens(data);
	if (status != 0)
		data->exit_status = status;
	else
		execute(data);
	if (status == 0)
		free_inst(data);
	return (0);
}
