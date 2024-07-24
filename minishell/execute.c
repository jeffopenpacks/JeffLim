/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 22:40:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/06/18 22:40:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sigint;

void	child_process(t_data *data, int inst_num)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (data->inst[inst_num]->redir)
		handle_redirection(data, inst_num);
	if (data->inst[0]->arr == NULL)
	{
		clean_exit(data);
		exit(EXIT_SUCCESS);
	}
	if (is_built_in(data, inst_num))
		built_ins(data, inst_num);
	else if (execve(data->inst[inst_num]->str, data->inst[inst_num]->arr,
			data->environ) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(pid_t pid, t_data *data)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = WTERMSIG(status) + 128;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	setup_parent_signals(t_data *data, int inst_num)
{
	if (data->inst[inst_num]->redir == NULL)
	{
		signal(SIGINT, handle_sigint_exec);
		signal(SIGQUIT, handle_sigquit_exec);
	}
}

//execute one command
void	exec_command(t_data *data, int inst_num)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_process(data, inst_num);
	else
	{
		setup_parent_signals(data, inst_num);
		parent_process(pid, data);
	}
}

//start the execution
void	execute(t_data *data)
{
	data->exit_status = 0;
	check_n_handle_heredoc(data);
	if (data->exit_status == 130)
		return ;
	if (data->inst == NULL)
		return ;
	if (data->inst[1] != NULL)
		exec_pipe(data);
	else
	{
		if (data->inst[0]->arr && is_built_in(data, 0))
			built_ins(data, 0);
		else if (find_executable(data, 0) == 1)
			exec_command(data, 0);
		else
			create_redir_files(data, 0);
	}
}
