/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:02:09 by joolim            #+#    #+#             */
/*   Updated: 2024/02/06 14:14:21 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include "libft/libft.h"

int		main(int argc, char **argv, char **envp);
void	file_in(char **argv);
void	free_all(char **arr);
void	error_exit(char *str);

#endif
