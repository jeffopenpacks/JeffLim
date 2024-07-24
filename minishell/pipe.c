/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:41:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/06/25 19:41:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//dup2 and close pipes
void	setup_child_pipes(int **pipes, int i, int npipes)
{
	if (i == 0)
		dup2(pipes[i][1], STDOUT_FILENO);
	else if (i == npipes)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	close_all_pipes(pipes, npipes);
}

//create all child processes and set their pipes
int	*fork_childs(t_data *data, int **pipes, int npipes)
{
	int	i;
	int	*pids;

	i = 0;
	pids = (int *)malloc(sizeof(int) * (npipes + 1));
	while (i < npipes + 1)
	{
		pids[i] = fork();
		if (pids[i++] == 0)
		{
			setup_child_pipes(pipes, i - 1, npipes);
			if (data->inst[i - 1]->arr && is_built_in(data, i - 1))
				built_ins(data, i - 1);
			else if (find_executable(data, i - 1))
				child_process(data, i - 1);
			else
				create_redir_files(data, i - 1);
			clean_exit(data);
			free_int_arr(pipes);
			free(pids);
			exit(data->exit_status);
		}
	}
	close_all_pipes(pipes, npipes);
	return (pids);
}

//create pipes
int	**create_pipes(int npipes)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = (int **)malloc(sizeof(int *) * (npipes + 1));
	if (!pipes)
		return (NULL);
	while (i < npipes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			free_int_arr(pipes);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			free_int_arr(pipes);
			return (NULL);
		}
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

//count the number of pipes, simply the lenght of data->inst - 1
int	count_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (data->inst[i])
		i++;
	return (i - 1);
}

//set up pipes for the commands
void	exec_pipe(t_data *data)
{
	int	npipes;
	int	**pipes;
	int	*pids;

	npipes = count_pipes(data);
	pipes = create_pipes(npipes);
	if (!pipes)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pids = fork_childs(data, pipes, npipes);
	wait_for_childs(data, pids, npipes + 1);
	free_int_arr(pipes);
	free(pids);
}
