/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:42:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/07/18 17:42:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_character_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
	}
	free(arr);
}

int	is_directory(t_data *data, char *path, int inst_num)
{
	char	*temp;
	char	*full_path;
	DIR		*dir;

	temp = ft_strjoin(path, "/");
	dir = opendir(temp);
	if (!dir)
		return (0);
	closedir(dir);
	full_path = ft_strjoin(temp, data->inst[inst_num]->arr[0]);
	free(temp);
	if (!full_path)
	{
		perror("ft_strjoin");
		exit(EXIT_FAILURE);
	}
	if (access(full_path, F_OK) == 0)
	{
		free(full_path);
		return (1);
	}
	free(full_path);
	return (0);
}

void	print_cmd_not_found(t_data *data, int inst_num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->inst[inst_num]->arr[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	data->exit_status = 127;
}

void	print_no_file_dir(t_data *data, int inst_num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->inst[inst_num]->arr[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	data->exit_status = 127;
}

void	print_is_dir(t_data *data, int inst_num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->inst[inst_num]->arr[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	data->exit_status = 126;
}
