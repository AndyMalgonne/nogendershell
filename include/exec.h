/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:46:06 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/27 20:01:25 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "data_struct.h"

typedef struct s_fds
{
	int		infd;
	int		outfd;
	int		heredocfd;
	int		prev_fd;
	pid_t	pid;
}	t_fds;

typedef struct s_env	t_env;

// Builtin functions
int		bi_pwd(const t_tree *node, t_var *var);
int		bi_env(const t_tree *node, t_var *var);
int		bi_exit(const t_tree *node, t_var *var, t_fds *fds);
int		bi_echo(char **args, t_var *var);
int		bi_unset(char **cmd, t_var **var);
int		bi_export(const t_tree *node, t_var *var);
int		using_export(const char *id, t_var *var);
int		bi_cd(char **cmd, t_var *var);

// Builtin exec functions
int		handle_builtin(t_fds *fds, int pip[2], t_tree *cmd, t_var *env);
void	launch_builtin(t_fds *fds, int pip[2], t_tree *cmd, t_var *env);

// Exec functions
int		minishell_exec(t_tree *cmd, t_var *var);
void	exec_cmd(const t_tree *cmd, t_var *var);
void	children_process(t_fds *fds, int pip[2], t_tree *cmd, t_var *var);
void	parent_process(t_fds *fds, int pip[2], const t_tree *cmd);

// Redir functions
void	redir(t_fds *fds, int pip[2], const t_tree *cmd, t_var *var);
int		io_files(t_iofile *io, t_fds *fds);
void	close_fds(t_fds *fds);

// Path functions
char	*find_file(char *cmd, t_var *var);

// Here_doc functions
char	*r_name(unsigned char r_bytes[], const char alpha[],
			int alpha_size, int size);
int		get_random_bytes(unsigned char random_bytes[], int size);
void	increment_random_bytes(unsigned char random_bytes[], int alphanum_size);
int		process_heredoc(t_tree *cmd, t_fds *fds, t_var *var);

// Here_doc expand functions
int		expand_heredoc_value(char **value, t_var *var);

// Utils functions
int		wait_children(int pid, int old_code);
void	init_and_reset_pipes(int pip[2]);
void	init_fds_and_pid(t_fds *fds);

// Utils2 functions
int		handle_heredoc(t_tree *cmd, t_fds *fds, t_var *var);
int		handle_builtin_next(t_fds *fds, int pip[2], t_tree **cmd, t_var *env);
int		handle_fork(t_fds *fds, int pip[2], t_tree *cmd, t_var *var);

#endif
