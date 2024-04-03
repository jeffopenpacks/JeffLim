/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:30 by joolim            #+#    #+#             */
/*   Updated: 2024/02/06 14:26:33 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_all(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	file_in(char **argv)
{
	int	pipe_fd[2];

	pipe_fd[0] = open(argv[1], O_RDONLY);
	if (pipe_fd[0] == -1)
		error_exit("Error reading file");
	dup2(pipe_fd[0], STDIN_FILENO);
}
