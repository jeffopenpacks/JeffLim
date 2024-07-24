/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:26:51 by joolim            #+#    #+#             */
/*   Updated: 2024/07/12 11:28:31 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pop_env(t_data *data, int j)
{
	char	**buf;
	int		i;

	buf = NULL;
	i = 0;
	while (data->environ[i])
		i++;
	buf = (char **)malloc(i * sizeof(char *));
	safe_fn(buf, data);
	i = 0;
	while (i < j)
	{
		buf[i] = (char *)safe_fn(ft_strdup(data->environ[i]), data);
		i++;
	}
	j++;
	while (data->environ[j])
		buf[i++] = (char *)safe_fn(ft_strdup(data->environ[j++]), data);
	buf[i] = NULL;
	free_environ(data->environ);
	data->environ = buf;
}

int	ft_unset(t_data *data, t_inst *inst)
{
	int	i;
	int	j;
	int	l;

	i = 1;
	j = 0;
	l = ft_strlen(inst->arr[i]);
	if (!data->environ)
		return (0);
	while (inst->arr[i])
	{
		while (data->environ[j])
		{
			if (ft_strncmp(data->environ[j], inst->arr[i], l) == 0)
			{
				if (data->environ[j][l] == '\0' || data->environ[j][l] == '=')
					pop_env(data, j);
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
