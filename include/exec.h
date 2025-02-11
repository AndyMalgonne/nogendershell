/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andytropmimi <andytropmimi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:46:06 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/10 10:08:40 by andytropmim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "data_struct.h"

// Builtin functions

typedef struct s_env	t_env;

int		bi_pwd(void);
int		bi_echo(char **args);
int		bi_env(t_env *env);
int		bi_unset(char **str, t_env **env);

// Exec functions
int		minishell_exec(t_tree *cmd, t_var *var);
int		exec_cmd(t_tree *cmd, const int *pip, t_var *var);

// Path functions
char	*find_file(char *cmd, t_var *var);

// Here_doc functions
char	*find_heredoc_file(void);
char	*r_name(unsigned char r_bytes[], const char alpha[],
			int alpha_size, int size);
int		get_random_bytes(unsigned char random_bytes[], int size);
void	increment_random_bytes(unsigned char random_bytes[], int alphanum_size);

#endif
