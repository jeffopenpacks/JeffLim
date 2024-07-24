/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:09:15 by joolim            #+#    #+#             */
/*   Updated: 2024/07/12 09:47:05 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eof_exit(t_data *data, int status)
{
	printf("exit\n");
	if (data->environ)
		free_environ(data->environ);
	exit(status);
}

static int	exit_act(int status, t_inst *inst)
{
	int	count;

	count = 0;
	if (inst->arr[1][count] == '-' || inst->arr[1][count] == '+')
		count++;
	while (inst->arr[1][count])
	{
		if (!ft_isdigit(inst->arr[1][count]))
			status = 2;
		count++;
	}
	if (status == 0)
		status = ft_atoi(inst->arr[1]);
	else
		printf("exit: Invalid exit code.\n");
	return (status);
}

int	ft_exit(t_data *data, t_inst *inst)
{
	int	count;
	int	status;

	count = 0;
	status = 0;
	while (inst->arr[count])
		count++;
	if (count > 2)
	{
		printf("exit: Too many arguments.\n");
		return (1);
	}
	if (count == 2)
		status = exit_act(status, inst);
	free(data->input);
	free_inst(data);
	free_environ(data->environ);
	exit(status);
	return (status);
}
