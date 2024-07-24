/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:52:33 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 14:53:22 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_fn(void *ptr, t_data *data)
{
	if (!ptr)
	{
		perror("malloc failed");
		if (data->tokens)
			free_tokens(data);
		if (data->inst)
			free_inst(data);
		free_environ(data->environ);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
