/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolla.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:02:15 by joolim            #+#    #+#             */
/*   Updated: 2024/07/14 11:28:37 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_freevar(char *value, char *buf, char *str)
{
	if (buf)
		free(buf);
	if (value)
		free(value);
	if (str)
		free(str);
}

static int	replace_var(t_token *token, int i, char *tmp, char *value)
{
	int		j;
	char	*buf;

	j = 0;
	buf = NULL;
	while (j < i && token->str[j])
		tmp = ft_strjoin_char(tmp, token->str[j++]);
	if (token->str[i + 1] == '?')
	{
		i += 2;
		buf = ft_itoa(token->data->exit_status);
		tmp = ft_strjoin_gnl(tmp, buf);
	}
	else
	{
		i++;
		while (ft_isalnum(token->str[i]) != 0 || token->str[i] == '_')
			value = ft_strjoin_char(value, token->str[i++]);
		tmp = ft_strjoin_gnl(tmp, ft_getenv(token->data->environ, value));
	}
	j = ft_strlen(tmp);
	tmp = ft_strjoin_gnl(tmp, &(token->str[i]));
	cleanup_freevar(value, buf, token->str);
	token->str = tmp;
	return (j);
}

static int	move_iter(t_token *tokens, int i)
{
	i++;
	while (tokens->str[i] && tokens->str[i] != '\'')
		i++;
	i++;
	return (i);
}

static void	expand_dolla(t_token *tokens, int i, int flag)
{
	while (tokens->str[i])
	{
		if (tokens->str[i] == '"')
			flag *= -1;
		if (tokens->str[i] == '\'' && flag > 0)
			i = move_iter(tokens, i);
		else if (tokens->str[i] == '$')
		{
			if ((ft_isalnum(tokens->str[i + 1]) == 0 \
						&& ft_strchr("_?", tokens->str[i + 1]) == 0) \
					|| !(tokens->str[i + 1]))
			{
				i++;
				continue ;
			}
			else
				i = replace_var(tokens, i, NULL, NULL);
		}
		else
			i++;
	}
}

void	dolla(t_token **tokens)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (tokens[i])
	{
		j = 0;
		flag = 1;
		if (ft_strchr(tokens[i]->str, '$') != 0)
			expand_dolla(tokens[i], j, flag);
		i++;
	}
}
