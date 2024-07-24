/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:15:23 by joolim            #+#    #+#             */
/*   Updated: 2024/07/21 10:47:48 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint = 0;

static int	check_quotes(char *input)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (ft_strchr(input, '\'') == 0 && ft_strchr(input, '"') == 0)
		return (0);
	while (i < ft_strlen(input))
	{
		while (input[i] != '\'' && input[i] != '"' && input[i])
			i++;
		if (input[i] == '\'' && flag == 0)
			flag = 1;
		else if (input[i] == '\'' && flag == 1)
			flag = 0;
		else if (input[i] == '"' && flag == 0)
			flag = 2;
		else if (input[i] == '"' && flag == 2)
			flag = 0;
		i++;
	}
	return (flag);
}

static int	check_input(char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]) != 0)
		i++;
	if (input[i] == '\0')
		return (1);
	else if (check_quotes(input) == 1)
	{
		printf("Error: Unclosed single quote\n");
		return (2);
	}
	else if (check_quotes(input) == 2)
	{
		printf("Error: Unclosed double quote\n");
		return (2);
	}
	return (0);
}

static void	init_data(t_data *data, char **envp, int option)
{
	if (option == 0)
	{
		data->environ = copy_environ(envp, 0, 0);
		data->exit_status = 0;
		data->tokens = NULL;
		data->inst = NULL;
		data->input = NULL;
		init_sig();
	}
	if (option == 1)
	{
		data->exit_status = 130;
		g_sigint = 0;
	}
}

static void	empty_env(void)
{
	write(2, "Error: Env not found.", 21);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	if (!envp)
		empty_env();
	init_data(&data, envp, 0);
	while (1)
	{
		data.input = readline("minishell> ");
		if (g_sigint == 2)
			init_data(&data, envp, 1);
		if (!data.input)
			eof_exit(&data, 130);
		if (data.input[0] != '\0')
			add_history(data.input);
		if (check_input(data.input) == 0)
			process(data.input, &data);
		else
			data.exit_status = check_input(data.input);
		free(data.input);
	}
	if (data.environ)
		free_environ(data.environ);
	return (0);
}
