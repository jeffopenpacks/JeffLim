/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:11:56 by joolim            #+#    #+#             */
/*   Updated: 2024/07/21 11:22:02 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_and_exit(char **env, char *str, int option)
{
	if (option == 1)
		free_environ(env);
	perror(str);
	exit(EXIT_FAILURE);
}

void	add_environ(t_data *data, char *key, char *value)
{
	int		c;
	char	**env2;

	c = 0;
	while (data->environ[c])
		c++;
	env2 = (char **)malloc((c + 2) * sizeof(char *));
	c = 0;
	while (data->environ[c])
	{
		env2[c] = (char *)safe_fn(ft_strdup(data->environ[c]), data);
		c++;
	}
	env2[c] = (char *)safe_fn(ft_strdup(key), data);
	env2[c] = (char *)safe_fn(ft_strjoin_char(env2[c], '='), data);
	env2[c] = (char *)safe_fn(ft_strjoin_gnl(env2[c], value), data);
	env2[c + 1] = NULL;
	c = 0;
	free_environ(data->environ);
	data->environ = env2;
}

void	update_environ(t_data *data, char *key, char *value)
{
	int		i;
	size_t	keylen;

	i = 0;
	keylen = ft_strlen(key);
	while (data->environ[i])
	{
		if (ft_strncmp(data->environ[i], key, keylen) == 0 \
				&& data->environ[i][keylen] == '=')
		{
			free(data->environ[i]);
			data->environ[i] = ft_strdup(key);
			data->environ[i] = ft_strjoin_char(data->environ[i], '=');
			data->environ[i] = ft_strjoin_gnl(data->environ[i], value);
			if (!data->environ[i])
				print_and_exit(data->environ, "env", 1);
			return ;
		}
		i++;
	}
	add_environ(data, key, value);
}

void	free_environ(char **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		free(environ[i]);
		environ[i] = NULL;
		i++;
	}
	if (environ != NULL)
	{
		free(environ);
		environ = NULL;
	}
}

char	**copy_environ(char **envp, int count, int i)
{
	char	**env_ptr;
	char	**new_environ;

	env_ptr = envp;
	while (*env_ptr != NULL)
	{
		count++;
		env_ptr++;
	}
	new_environ = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_environ)
		print_and_exit(NULL, "env", 0);
	while (i < count)
	{
		new_environ[i] = ft_strdup(envp[i]);
		if (new_environ[i] == NULL)
			print_and_exit(new_environ, "env", 1);
		i++;
	}
	new_environ[count] = NULL;
	return (new_environ);
}
