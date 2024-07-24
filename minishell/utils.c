/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:54:38 by joolim            #+#    #+#             */
/*   Updated: 2024/07/12 10:57:29 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **environ, const char *var)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(var, environ[i], ft_strlen(var)) == 0 \
				&& environ[i][ft_strlen(var)] == '=')
			return (environ[i] + ft_strlen(var) + 1);
		i++;
	}
	return ("");
}

static void	free_token(t_data *data, int i)
{
	if (data->tokens[i]->str)
		free(data->tokens[i]->str);
	free(data->tokens[i]);
}

void	pop_token(t_data *data, int i)
{
	int		count;
	int		j;
	int		k;
	t_token	**tmp;

	count = 0;
	j = 0;
	k = i;
	while (data->tokens[j++])
		count++;
	tmp = (t_token **)malloc((count + 1) * (sizeof(t_token *)));
	tmp[count] = NULL;
	j = 0;
	while (j < i)
	{
		tmp[j] = data->tokens[j];
		j++;
	}
	free_token(data, i);
	k++;
	while (data->tokens[k])
		tmp[j++] = data->tokens[k++];
	tmp[j] = NULL;
	free(data->tokens);
	data->tokens = tmp;
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' \
			|| c == '\f' || c == '\r');
}

char	*ft_strjoin_char(char *str1, char c)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!str1)
	{
		str1 = malloc(1);
		str1[0] = '\0';
	}
	tmp = malloc((ft_strlen_gnl(str1)) + 2);
	if (!tmp)
		return (NULL);
	while (str1[++i] != '\0')
		tmp[i] = str1[i];
	tmp[i++] = c;
	tmp[i] = '\0';
	free(str1);
	return (tmp);
}
