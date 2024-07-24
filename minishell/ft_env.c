/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:08:45 by joolim            #+#    #+#             */
/*   Updated: 2024/07/11 17:08:47 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, t_inst *inst, int fd)
{
	int	count;

	count = 0;
	while (inst->arr[count])
		count++;
	if (count > 1)
	{
		printf("env: Too many arguments\n");
		return (1);
	}
	count = 0;
	while (data->environ[count])
	{
		if (ft_strchr(data->environ[count], '=') == NULL)
		{
			count++;
			continue ;
		}
		ft_putstr_fd(data->environ[count++], fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}
