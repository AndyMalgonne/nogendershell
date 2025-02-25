/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:46:06 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/25 21:09:09 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "data_struct.h"

typedef struct s_fds
{
	int	infd;
	int	outfd;
	int	heredocfd;
	int	prev_fd;
}	t_fds;

typedef struct s_env	t_env;

// Builtin functions
int		bi_pwd(void);
int		bi_env(t_var *env, const char *key);
int		bi_echo(char **args, t_var *var);
int		bi_unset(char **str, t_env **env);

// Builtin exec functions
int		handle_builtin(t_fds *fds, int pip[2], t_tree *cmd, t_var *env);
void	launch_builtin(t_fds *fds, const int pip[2], t_tree *cmd, t_var *env);

// Exec functions
int		minishell_exec(t_tree *cmd, t_var *var);
void	exec_cmd(const t_tree *cmd, t_var *var);
void	children_process(t_fds *fds, int pip[2], t_tree *cmd, t_var *var);

// Redir functions
void	redir(t_fds *fds, int pip[2], const t_tree *cmd, t_var *var);
int		io_files(t_iofile *io, t_fds *fds, t_var *var);
void	close_fds(t_fds *fds);

// Path functions
char	*find_file(char *cmd, t_var *var);

// Here_doc functions
char	*r_name(unsigned char r_bytes[], const char alpha[],
			int alpha_size, int size);
int		get_random_bytes(unsigned char random_bytes[], int size);
void	increment_random_bytes(unsigned char random_bytes[], int alphanum_size);
int		get_here_doc(char *del);
int		process_heredoc(t_tree *cmd, t_fds *fds);

// Utils functions
int		wait_children(int pid);
void	init_and_reset_pipes(int pip[2]);
void	init_fds_and_pid(t_fds *fds, pid_t *pid);

// Utils2 functions
int		handle_heredoc(t_tree *cmd, t_fds *fds, t_var *var);
int		handle_builtin_next(t_fds *fds, int pip[2], t_tree **cmd, t_var *env);
int		handle_fork(t_fds *fds, int pip[2], t_tree *cmd, t_var *var);

#endif
