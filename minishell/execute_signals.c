/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:40:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/06/18 22:40:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_exec(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	handle_sigquit_exec(int signum)
{
	(void) signum;
	write(2, "Quit (core dumped)\n", 19);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	print_infile_error(t_data *data, int inst_num, int redir_num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->inst[inst_num]->redir[redir_num]->str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	data->exit_status = 1;
}

void	create_redir_files(t_data *data, int inst_num)
{
	int	i;

	i = 0;
	if (data->inst[inst_num]->redir)
	{
		while (data->inst[inst_num]->redir[i])
		{
			if (data->inst[inst_num]->redir[i]->type == 3)
				open(data->inst[inst_num]->redir[i]->str, O_WRONLY | \
				O_CREAT | O_APPEND, 0644);
			else if (data->inst[inst_num]->redir[i]->type == 4)
				open(data->inst[inst_num]->redir[i]->str, O_WRONLY | \
				O_CREAT | O_TRUNC, 0644);
			else if (data->inst[inst_num]->redir[i]->type == 2)
			{
				if (access(data->inst[inst_num]->redir[i]->str, F_OK) == -1)
				{
					print_infile_error(data, inst_num, i);
					return ;
				}
			}
			i++;
		}
	}
}
