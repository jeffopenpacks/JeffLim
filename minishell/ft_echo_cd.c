/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:52:34 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 13:52:36 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_option(char *arr)
{
	int	res;
	int	i;

	res = 0;
	i = 1;
	if (ft_strncmp(arr, "-n", 2) == 0)
	{
		res = 1;
		while (arr[i])
		{
			if (arr[i] != 'n')
				res = 0;
			i++;
		}
	}
	return (res);
}

int	ft_echo(t_inst *inst, int fd)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (inst->arr[count])
		count++;
	if (count >= 2)
		flag += echo_option(inst->arr[1]);
	count = flag + 1;
	while (inst->arr[count])
	{
		ft_putstr_fd(inst->arr[count], fd);
		if (inst->arr[count + 1])
			ft_putchar_fd(' ', fd);
		count++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', fd);
	return (0);
}

static char	*remove_path(char *rpath, t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	if (ft_strlen(rpath) == 1 && rpath[0] == '/')
		printf("cd: cannot move up from top level directory\n");
	else
	{
		while (rpath[i])
		{
			if (rpath[i] == '/' && rpath[i + 1])
				j = i;
			i++;
		}
		tmp = malloc(j + 1);
		safe_fn(tmp, data);
		ft_strlcpy(tmp, rpath, j + 1);
		free(rpath);
		return (tmp);
	}
	return (rpath);
}

static char	*build_rpath(char **tokens, int i, char *rpath, t_data *data)
{
	while (tokens[i])
	{
		if (ft_strlen(tokens[i]) == 1 && tokens[i][0] == '.')
		{
		}
		else if (ft_strlen(tokens[i]) == 2 \
				&& ft_strncmp(tokens[i], "..", 2) == 0)
			rpath = remove_path(rpath, data);
		else
		{
			if (rpath[ft_strlen(rpath)] != '/')
				rpath = (char *)safe_fn(ft_strjoin_gnl(rpath, "/"), data);
			rpath = (char *)safe_fn(ft_strjoin(rpath, tokens[i]), data);
		}
		i++;
	}
	return (rpath);
}

char	*ft_rpath(char *src, char *rpath, char *buf, t_data *data)
{
	char	**tokens;
	int		i;

	i = 0;
	rpath = (char *)safe_fn(ft_strjoin_gnl(rpath, buf), data);
	tokens = (char **)safe_fn(ft_split(src, '/'), data);
	rpath = build_rpath(tokens, i, rpath, data);
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (rpath);
}
