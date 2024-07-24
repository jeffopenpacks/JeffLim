/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:41:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/06/29 19:41:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_output(t_data *data, int inst_num, int redir_num)
{
	int	fd;

	fd = open(data->inst[inst_num]->redir[redir_num]->str, O_WRONLY | \
			O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redir_append(t_data *data, int inst_num, int redir_num)
{
	int	fd;

	fd = open(data->inst[inst_num]->redir[redir_num]->str, O_WRONLY | \
			O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	redir_input(t_data *data, int inst_num, int redir_num)
{
	int	fd;

	fd = open(data->inst[inst_num]->redir[redir_num]->str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_redirection(t_data *data, int inst_num)
{
	int	i;
	int	nredir;

	i = 0;
	nredir = 0;
	while (data->inst[inst_num]->redir[nredir])
		nredir++;
	while (i < nredir)
	{
		if (data->inst[inst_num]->redir[i]->type == 2)
			redir_input(data, inst_num, i);
		else if (data->inst[inst_num]->redir[i]->type == 3)
			redir_append(data, inst_num, i);
		else if (data->inst[inst_num]->redir[i]->type == 4)
			redir_output(data, inst_num, i);
		i++;
	}
}
