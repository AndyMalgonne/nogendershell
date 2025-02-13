/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:33:38 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/13 12:44:31 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_struct.h"
# include "parsing.h"
# include "exec.h"
# include <stdbool.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

# define PROMPT "> "
# define ERR_MALLOC "Malloc error"

extern int			g_signal;

int		create_env(t_env **env, char **envp);
void	free_env(t_env **env);
void	print_env(const t_env *env);
int		get_input(char **user_input);
void	cleanup_user_input(char **user_input);
void	set_up_var(t_var *var);
void	free_var(t_var *var);
int		set_and_return_code(t_var *var, int code);

// t_env
char	*get_env_value(t_env *env, const char *key);
char	**get_path_from_env(t_env *env, int *error);
char	**linked_list_to_array(t_env *env);

// utils.c
void	*free_to_null(void *p);
int		mclose(int *fd);
int		error(t_var *var, const char *msg, int code);

#endif
