/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:59:54 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 14:04:30 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env(t_data *data, int count)
{
	if (!data->environ)
		count = 0;
	else
	{
		while (data->environ[count])
			count++;
	}
	return (count);
}

static int	ft_setvar(t_data *data, char *str)
{
	char	**tmp;
	int		count;

	count = count_env(data, 0);
	tmp = (char **)malloc((count + 2) * sizeof(char *));
	safe_fn(tmp, data);
	count = 0;
	if (data->environ)
	{
		while (data->environ[count])
		{
			tmp[count] = (char *)safe_fn(ft_strdup(data->environ[count]), data);
			count++;
		}
	}
	tmp[count] = (char *)safe_fn(ft_strdup(str), data);
	tmp[count + 1] = NULL;
	if (data->environ)
		free_environ(data->environ);
	data->environ = tmp;
	return (0);
}

static int	ft_checkvar(t_data *data, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (data->environ[j])
	{
		if (ft_strncmp(data->environ[j], str, i) == 0)
		{
			if (data->environ[j][i] && data->environ[j][i] == '=')
			{
				if (ft_strchr(str, '='))
				{
					pop_env(data, j);
					return (0);
				}
				else
					return (1);
			}
		}
		j++;
	}
	return (0);
}

static int	restof_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(t_data *data, t_inst *inst)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (inst->arr[0] && !inst->arr[1])
		return (ft_printexport(data));
	while (inst->arr[i])
	{
		if ((ft_isalpha(inst->arr[i][0]) == 0 && inst->arr[i][0] != '_') \
				|| restof_var(inst->arr[i]) != 0)
		{
			printf("export: %s invalid variable name\n", inst->arr[i]);
			j = 1;
		}
		else
		{
			if (ft_checkvar(data, inst->arr[i]) == 0)
				ft_setvar(data, inst->arr[i]);
		}
		i++;
	}
	return (j);
}
