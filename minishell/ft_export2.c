/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:55:35 by joolim            #+#    #+#             */
/*   Updated: 2024/07/13 14:05:17 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_envcmp(char **buf, int x, int y)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while ((buf[x][i] && buf[y][i]) && buf[x][i] != '=' && buf[y][i] != '=')
	{
		if (buf[x][i] == buf[y][i])
			i++;
		else
			break ;
	}
	j = (unsigned char)buf[x][i] - (unsigned char)buf[y][i];
	if (j > 0)
	{
		tmp = buf[x];
		buf[x] = buf[y];
		buf[y] = tmp;
	}
}

static void	ft_printexport3(char **buf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buf[i])
	{
		j = 0;
		printf("declare -x ");
		while (buf[i][j] && buf[i][j] != '=')
		{
			printf("%c", buf[i][j]);
			j++;
		}
		if (buf[i][j] == '=')
		{
			j++;
			printf("=\"%s\"", &buf[i][j]);
		}
		printf("\n");
		i++;
	}
}

static int	ft_printexport2(char **buf)
{
	int	i;
	int	j;

	i = 0;
	while (buf[i])
	{
		j = i + 1;
		while (buf[j])
		{
			ft_envcmp(buf, i, j);
			j++;
		}
		i++;
	}
	i = 0;
	ft_printexport3(buf);
	free_environ(buf);
	return (0);
}

int	ft_printexport(t_data *data)
{
	char	**buf;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!data->environ)
		count = 0;
	else
	{
		while (data->environ[count])
			count++;
	}
	buf = (char **)malloc((count + 1) * sizeof(char *));
	safe_fn(buf, data);
	while (data->environ[i])
	{
		buf[i] = (char *)safe_fn(ft_strdup(data->environ[i]), data);
		i++;
	}
	buf[i] = NULL;
	return (ft_printexport2(buf));
}
