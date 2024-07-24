/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:35:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/07/17 09:35:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sigint;

void	heredoc_write_to_file(t_data *data, char *str, int fd, char *filename)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (g_sigint == 130)
		{
			heredoc_interrupted(data, filename, fd);
			return ;
		}
		if (line == NULL)
		{
			print_heredoc_eof(str);
			break ;
		}
		else if (!ft_strncmp(line, str, ft_strlen(str)) && \
			ft_strlen(line) == ft_strlen(str) + 1)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

char	*create_heredoc_filename(int i, int j)
{
	char	*filename;
	char	*fileno;
	char	*temp;

	fileno = ft_itoa(i);
	filename = ft_strjoin("/tmp/heredoc_", fileno);
	free(fileno);
	temp = filename;
	filename = ft_strjoin(filename, "_");
	free(temp);
	fileno = ft_itoa(j);
	temp = filename;
	filename = ft_strjoin(filename, fileno);
	free(fileno);
	free(temp);
	return (filename);
}

void	read_heredoc_input(t_data *data, int inst_num, int redir_num)
{
	char	*filename;
	int		fd;

	filename = create_heredoc_filename(inst_num, redir_num);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(filename);
		data->exit_status = 1;
		clean_exit(data);
		exit(1);
	}
	heredoc_write_to_file(data, data->inst[inst_num]->redir[redir_num]->\
		str, fd, filename);
	if (data->exit_status == 130)
		return ;
	close(fd);
	free(data->inst[inst_num]->redir[redir_num]->str);
	data->inst[inst_num]->redir[redir_num]->str = filename;
	data->inst[inst_num]->redir[redir_num]->type = 2;
}

void	loop_through_redir(t_data *data, int inst_num)
{
	int		j;

	j = 0;
	while (data->inst[inst_num]->redir[j])
	{
		if (data->inst[inst_num]->redir[j]->type == 1)
			read_heredoc_input(data, inst_num, j);
		if (data->exit_status == 130)
			return ;
		j++;
	}
}

void	check_n_handle_heredoc(t_data *data)
{
	int		i;	

	set_heredoc_signals();
	i = 0;
	while (data->inst[i])
	{
		if (data->inst[i]->redir != NULL)
			loop_through_redir(data, i);
		if (data->exit_status == 130)
			return ;
		i++;
	}
	restore_signals();
}
