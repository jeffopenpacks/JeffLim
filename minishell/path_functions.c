/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 22:29:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/06/21 22:29:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_n_test_dir(t_data *data, char **paths, int inst_num)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		if (is_directory(data, paths[i], inst_num))
		{
			temp = ft_strjoin(paths[i], "/");
			full_path = ft_strjoin(temp, data->inst[inst_num]->arr[0]);
			free(temp);
			break ;
		}
		i++;
	}
	if (!paths[i])
	{
		print_cmd_not_found(data, inst_num);
		return (NULL);
	}
	free_character_arr(paths);
	return (full_path);
}

int	is_relative_path(t_data *data, int inst_num)
{
	if (ft_strncmp(data->inst[inst_num]->arr[0], "/", 1) == 0 || \
			ft_strncmp(data->inst[inst_num]->arr[0], "./", 2) == 0 || \
			ft_strncmp(data->inst[inst_num]->arr[0], "../", 3) == 0)
	{
		if (access(data->inst[inst_num]->arr[0], F_OK | X_OK) == 0)
		{
			data->inst[inst_num]->str = ft_strdup(data->inst[inst_num]->arr[0]);
			return (1);
		}
		else
		{
			print_no_file_dir(data, inst_num);
			return (2);
		}
	}
	return (0);
}

int	find_path_in_env(t_data *data, int inst_num)
{
	int	i;

	i = 0;
	while (data->environ[i])
	{
		if (ft_strncmp(data->environ[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (data->environ[i] == NULL)
	{
		print_no_file_dir(data, inst_num);
		return (-1);
	}
	return (i);
}

char	*build_full_path(t_data *data, int i, int inst_num)
{
	char	**paths;
	char	*full_path;

	paths = ft_split(data->environ[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	full_path = build_n_test_dir(data, paths, inst_num);
	if (full_path == NULL)
	{
		free_character_arr(paths);
		return (NULL);
	}
	else
		data->inst[inst_num]->str = full_path;
	return (full_path);
}

//check if the command is in the path and build the full command
int	find_executable(t_data *data, int inst_num)
{
	int		i;
	char	*full_path;
	DIR		*dir;

	if (data->inst[inst_num]->arr == NULL)
		return (0);
	dir = opendir(data->inst[inst_num]->arr[0]);
	if (dir != NULL)
	{
		print_is_dir(data, inst_num);
		closedir(dir);
		return (0);
	}
	i = is_relative_path(data, inst_num);
	if (i == 1)
		return (1);
	else if (i == 2)
		return (0);
	i = find_path_in_env(data, inst_num);
	if (i == -1)
		return (0);
	full_path = build_full_path(data, i, inst_num);
	if (full_path == NULL)
		return (0);
	return (1);
}
