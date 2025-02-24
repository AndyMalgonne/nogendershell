/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:46:06 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/24 18:21:12 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "data_struct.h"

typedef struct s_fds
{
	int	infd;
	int	outfd;
	int	prev_fd;
}	t_fds;

typedef struct s_env	t_env;

// Builtin functions
int		bi_pwd(void);
int		bi_echo(char **args);
int		bi_env(t_env *env);
int		bi_unset(char **str, t_env **env);

// Builtin exec functions
int		handle_builtin(t_fds *fds, int pip[2], t_tree *cmd);
bool	is_builtin(const t_tree *cmd);
void	launch_builtin(t_fds *fds, int pip[2], t_tree *cmd);

// Exec functions
int		minishell_exec(t_tree *cmd, t_var *var);
void	exec_cmd(const t_tree *cmd, t_var *var);

// Redir functions
void	redir(t_fds *fds, int pip[2], const t_tree *cmd, t_var *var);
int		io_files(t_iofile *io, t_fds *fds);
void	close_fds(t_fds *fds);

// Path functions
char	*find_file(char *cmd, t_var *var);

// Here_doc functions
char	*find_heredoc_file(void);
char	*r_name(unsigned char r_bytes[], const char alpha[],
			int alpha_size, int size);
int		get_random_bytes(unsigned char random_bytes[], int size);
void	increment_random_bytes(unsigned char random_bytes[], int alphanum_size);

// Utils functions
int		wait_children(int pid);
void	init_and_reset_pipes(int pip[2]);


#endif
