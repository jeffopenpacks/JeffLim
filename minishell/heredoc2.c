/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:26:00 by jiheng            #+#    #+#             */
/*   Updated: 2024/07/18 16:26:00 by jiheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sigint;

void	handle_sigint_heredoc(int signum)
{
	(void)signum;
	g_sigint = 130;
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	print_heredoc_eof(char *str)
{
	printf("minishell: warning: here-document delimited by end-of-file");
	printf(" (wanted `%s')\n", str);
}

void	heredoc_interrupted(t_data *data, char *filename, int fd)
{
	write(1, "\n", 1);
	free(filename);
	close(fd);
	data->exit_status = 130;
	g_sigint = 0;
	restore_signals();
}
