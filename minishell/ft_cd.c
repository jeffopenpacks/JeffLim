/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:52:23 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 13:52:25 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*home_path(t_data *data, char *buf)
{
	int		i;
	int		k;
	char	*path;

	i = 0;
	k = 0;
	path = NULL;
	while (data->environ[i])
	{
		if (ft_strncmp(data->environ[i], "HOME=", 5) == 0)
		{
			k = 1;
			break ;
		}
		i++;
	}
	if (k == 1)
		path = (char *)safe_fn(ft_strdup(&data->environ[i][5]), data);
	else
	{
		printf("cd: Home directory not found\n");
		path = (char *)safe_fn(ft_strdup(buf), data);
	}
	return (path);
}

static void	end_cd(t_data *data, char *buf, char *rpath)
{
	update_environ(data, "OLDPWD", buf);
	free(buf);
	buf = NULL;
	buf = getcwd(NULL, 0);
	update_environ(data, "PWD", buf);
	free(buf);
	buf = NULL;
	free(rpath);
	rpath = NULL;
}

static char	*alt_path(t_data *data, t_inst *inst, char *buf)
{
	char	*rpath;

	rpath = NULL;
	if (inst->arr[1][0] == '/')
		rpath = (char *)safe_fn(ft_strdup(inst->arr[1]), data);
	else if (inst->arr[1][0] == '~')
	{
		rpath = home_path(data, buf);
		rpath = (char *)safe_fn(ft_strjoin_gnl(rpath, &inst->arr[1][1]), data);
	}
	else
		rpath = ft_rpath(inst->arr[1], rpath, buf, data);
	return (rpath);
}

static int	path_error(int option)
{
	if (option == 1)
		perror("cd: chdir error");
	else if (option == 2)
		printf("cd: Too many arguments.\n");
	else if (option == 3)
		perror("cd: getcwd error");
	return (1);
}

int	ft_cd(t_data *data, t_inst *inst)
{
	char	*buf;
	char	*rpath;
	int		count;

	count = 0;
	rpath = NULL;
	while (inst->arr[count])
		count++;
	if (count == 2 && ft_strlen(inst->arr[1]) == 0)
		return (0);
	if (count > 2)
		return (path_error(2));
	buf = getcwd(NULL, 0);
	if (!buf)
		return (path_error(3));
	if (count == 1)
		rpath = home_path(data, buf);
	else
		rpath = alt_path(data, inst, buf);
	if (chdir(rpath) != 0)
		return (path_error(1));
	end_cd(data, buf, rpath);
	return (0);
}
