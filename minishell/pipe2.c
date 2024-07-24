/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:01:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/06/25 23:01:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_childs(t_data *data, int *pids, int nchilds)
{
	int	i;
	int	status;

	i = 0;
	while (i < nchilds)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_status = WTERMSIG(status) + 128;
		i++;
	}
}

void	free_int_arr(int **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	close_all_pipes(int **pipes, int npipes)
{
	int	i;

	i = 0;
	while (i < npipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
