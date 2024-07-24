/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:06:54 by joolim            #+#    #+#             */
/*   Updated: 2024/07/11 17:08:06 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **arg)
{
	char	*buf;

	(void) arg;
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("getcwd error");
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}
