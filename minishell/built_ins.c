/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:41:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/06/25 19:41:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_restore(int *fd_std)
{
	dup2(fd_std[0], STDIN_FILENO);
	dup2(fd_std[1], STDOUT_FILENO);
	dup2(fd_std[2], STDERR_FILENO);
	close(fd_std[0]);
	close(fd_std[1]);
	close(fd_std[2]);
}

void	fd_backup(int *fd_std)
{
	fd_std[0] = dup(STDIN_FILENO);
	fd_std[1] = dup(STDOUT_FILENO);
	fd_std[2] = dup(STDERR_FILENO);
}

void	execute_built_ins(t_data *data, int i)
{
	if (data->inst[i]->redir)
		handle_redirection(data, i);
	if (ft_strlen(data->inst[i]->arr[0]) == 4
		&& ft_strncmp(data->inst[i]->arr[0], "echo", 4) == 0)
		data->exit_status = ft_echo(data->inst[i], 1);
	if (ft_strlen(data->inst[i]->arr[0]) == 2
		&& ft_strncmp(data->inst[i]->arr[0], "cd", 2) == 0)
		data->exit_status = ft_cd(data, data->inst[i]);
	if (ft_strlen(data->inst[i]->arr[0]) == 3
		&& ft_strncmp(data->inst[i]->arr[0], "pwd", 3) == 0)
		data->exit_status = ft_pwd(data->inst[i]->arr);
	if (ft_strlen(data->inst[i]->arr[0]) == 6
		&& ft_strncmp(data->inst[i]->arr[0], "export", 6) == 0)
		data->exit_status = ft_export(data, data->inst[i]);
	if (ft_strlen(data->inst[i]->arr[0]) == 5
		&& ft_strncmp(data->inst[i]->arr[0], "unset", 5) == 0)
		data->exit_status = ft_unset(data, data->inst[i]);
	if (ft_strlen(data->inst[i]->arr[0]) == 3
		&& ft_strncmp(data->inst[i]->arr[0], "env", 3) == 0)
		data->exit_status = ft_env(data, data->inst[i], 1);
	if (ft_strlen(data->inst[i]->arr[0]) == 4
		&& ft_strncmp(data->inst[i]->arr[0], "exit", 4) == 0)
		data->exit_status = ft_exit(data, data->inst[i]);
}

void	built_ins(t_data *data, int i)
{
	int	fd_std[3];

	fd_backup(fd_std);
	execute_built_ins(data, i);
	fd_restore(fd_std);
}

int	is_built_in(t_data *data, int i)
{
	if (ft_strlen(data->inst[i]->arr[0]) == 4
		&& ft_strncmp(data->inst[i]->arr[0], "echo", 4) == 0)
		return (1);
	if (ft_strlen(data->inst[i]->arr[0]) == 2
		&& ft_strncmp(data->inst[i]->arr[0], "cd", 2) == 0)
		return (1);
	if (ft_strlen(data->inst[i]->arr[0]) == 3
		&& ft_strncmp(data->inst[i]->arr[0], "pwd", 3) == 0)
		return (1);
	if (ft_strlen(data->inst[i]->arr[0]) == 6
		&& ft_strncmp(data->inst[i]->arr[0], "export", 6) == 0)
		return (1);
	if (ft_strlen(data->inst[i]->arr[0]) == 5
		&& ft_strncmp(data->inst[i]->arr[0], "unset", 5) == 0)
		return (1);
	if (ft_strlen(data->inst[i]->arr[0]) == 3
		&& ft_strncmp(data->inst[i]->arr[0], "env", 3) == 0)
		return (1);
	if (ft_strlen(data->inst[i]->arr[0]) == 4
		&& ft_strncmp(data->inst[i]->arr[0], "exit", 4) == 0)
		return (1);
	return (0);
}
