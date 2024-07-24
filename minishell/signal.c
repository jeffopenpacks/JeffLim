/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:52:23 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 13:52:25 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sigint;

void	sig_handler(int signum)
{
	if (signum < 2 || signum > 3)
		return ;
	rl_on_new_line();
	if (signum == 2)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
	}
	if (signum == 3)
		write(1, "\33[2K\r", 5);
	rl_redisplay();
	g_sigint = signum;
}

void	init_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
