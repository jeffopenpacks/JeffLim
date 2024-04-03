/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:04:58 by joolim            #+#    #+#             */
/*   Updated: 2024/02/06 14:29:17 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	create_outfile(int argc, char **argv)
{
	int	out_fd;

	out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_fd == -1)
		error_exit("Can't open output file");
	return (out_fd);
}

static char	*make_path(char **path_env, char *cmd)
{
	char	*path;
	char	*prepath;
	int		i;

	i = 0;
	path = malloc(1);
	ft_memset(path, 0, sizeof(path));
	while (path_env[i])
	{
		prepath = ft_strjoin(path_env[i], "/");
		path = ft_strjoin(prepath, cmd);
		free(prepath);
		if (access(path, F_OK) == 0)
		{
			free_all(path_env);
			return (path);
		}
		free(path);
		i++;
	}
	free_all(path_env);
	return (0);
}

static void	execute(char *cmd, char **envp)
{
	char	**cmdargs;
	char	*path;
	char	**path_env;
	int		result;
	int		i;

	i = 0;
	cmdargs = ft_split(cmd, ' ');
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	path_env = ft_split(envp[i] + 5, ':');
	if (!cmdargs || !path_env)
		error_exit("Unable to find path");
	path = NULL;
	path = make_path(path_env, cmdargs[0]);
	result = execve(path, cmdargs, envp);
	free_all(cmdargs);
	if (result == -1)
		error_exit("cmd execution failed");
}

static void	make_cmd(char *cmd, char **envp)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd) == -1)
		error_exit("pipe failure");
	pid = fork();
	if (pid == -1)
		error_exit("Failed to fork");
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		execute(cmd, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	outfile;
	int	i;

	i = 0;
	if (argc != 5)
		error_exit("Please provide 4 args");
	file_in(argv);
	i = 2;
	outfile = create_outfile(argc, argv);
	while (i < (argc - 2))
		make_cmd(argv[i++], envp);
	dup2(outfile, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
}
