/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:09:52 by joolim            #+#    #+#             */
/*   Updated: 2024/07/21 10:48:00 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <dirent.h>
# include "./libft/libft.h"

struct	s_token;
struct	s_inst;
struct	s_redir;

typedef struct s_data
{
	char			**environ;
	char			**exports;
	char			*input;
	int				exit_status;
	int				exit;	
	struct s_token	**tokens;
	struct s_inst	**inst;
}	t_data;

typedef struct s_token
{
	char			*str;
	int				type;
	int				pos;
	struct s_data	*data;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_inst
{
	struct s_data	*data;
	struct s_redir	**redir;
	char			**arr;
	char			*str;
}	t_inst;

typedef struct s_redir
{
	char	*str;
	int		type;
}	t_redir;

int		main(int argc, char **argv, char **envp);
char	**copy_environ(char **envp, int count, int i);
void	free_environ(char **environ);
void	init_sig(void);
int		ft_isspace(int c);
int		process(char *input, t_data *data);
void	find_tokens(char *input, t_data *data);
int		make_tokens(char *str, t_token *tokens, int pos, int option);
int		parse(t_data *data);
char	*ft_strjoin_char(char *str1, char c);
char	*ft_rddup(char *str, t_data *data);
void	*safe_fn(void *ptr, t_data *data);
void	dolla(t_token **tokens);
void	pop_token(t_data *data, int i);
void	free_tokens(t_data *data);
void	add_environ(t_data *data, char *key, char *value);
void	update_environ(t_data *data, char *key, char *value);
int		ft_echo(t_inst *inst, int fd);
int		ft_cd(t_data *data, t_inst *inst);
int		ft_pwd(char **arg);
int		ft_export(t_data *data, t_inst *inst);
int		ft_printexport(t_data *data);
int		ft_unset(t_data *data, t_inst *inst);
int		ft_env(t_data *data, t_inst *inst, int fd);
int		ft_exit(t_data *data, t_inst *inst);
void	pop_env(t_data *data, int j);
t_redir	**handle_redir(t_data *data, int j, int count);
void	init_inst(t_data *data, int count);
char	*ft_rpath(char *src, char *rpath, char *buf, t_data *data);
char	*ft_getenv(char **environ, const char *var);
void	remove_quotes(t_token *token, int i);
void	free_inst(t_data *data);
void	sig_handler(int signum);
void	eof_exit(t_data *data, int status);

//execute.c
void	execute(t_data *data);
void	exec_command(t_data *data, int inst_num);
void	setup_parent_signals(t_data *data, int inst_num);
void	parent_process(pid_t pid, t_data *data);
void	child_process(t_data *data, int inst_num);
//execute_signals.c
void	handle_sigquit_exec(int signum);
void	handle_sigint_exec(int signum);
void	create_redir_files(t_data *data, int inst_num);
//built_ins.c
int		is_built_in(t_data *data, int i);
void	built_ins(t_data *data, int i);
void	execute_built_ins(t_data *data, int i);
void	fd_backup(int *fd_std);
void	fd_restore(int *fd_std);
//path_functions.c
int		find_executable(t_data *data, int inst_num);
char	*build_full_path(t_data *data, int i, int inst_num);
int		find_path_in_env(t_data *data, int inst_num);
int		is_relative_path(t_data *data, int inst_num);
char	*build_n_test_dir(t_data *data, char **paths, int inst_num);
//path_functions2.c
void	print_is_dir(t_data *data, int inst_num);
void	print_no_file_dir(t_data *data, int inst_num);
void	print_cmd_not_found(t_data *data, int inst_num);
int		is_directory(t_data *data, char *path, int inst_num);
void	free_character_arr(char **arr);
//pipe.c
void	exec_pipe(t_data *data);
int		count_pipes(t_data *data);
int		**create_pipes(int npipes);
int		*fork_childs(t_data *data, int **pipes, int npipes);
void	setup_child_pipes_heredoc(int **pipes, int i, int npipes);
void	setup_child_pipes(int **pipes, int i, int npipes);
//pipe2.c
void	close_all_pipes_heredoc(int **pipes, int npipes);
void	close_all_pipes(int **pipes, int npipes);
void	free_int_arr(int **arr);
void	wait_for_childs(t_data *data, int *pids, int nchilds);
//redirection.c
void	handle_redirection(t_data *data, int inst_num);
void	redir_input(t_data *data, int inst_num, int redir_num);
void	redir_append(t_data *data, int inst_num, int redir_num);
void	redir_output(t_data *data, int inst_num, int redir_num);
//heredoc.c
void	check_n_handle_heredoc(t_data *data);
void	loop_through_redir(t_data *data, int inst_num);
void	read_heredoc_input(t_data *data, int inst_num, int redir_num);
char	*create_heredoc_filename(int i, int j);
void	heredoc_write_to_file(t_data *data, char *str, int fd, char *filename);
//heredoc2.c
void	heredoc_interrupted(t_data *data, char *filename, int fd);
void	print_heredoc_eof(char *str);
void	restore_signals(void);
void	set_heredoc_signals(void);
void	handle_sigint_heredoc(int signum);
//clean_exit.c
void	clean_exit(t_data *data);
void	free_inst_jl(t_data *data);
void	free_redir_jl(t_data *data, int inst_num);

#endif
