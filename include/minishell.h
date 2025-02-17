/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:33:38 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/17 14:24:19 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_struct.h"
# include "parsing.h"
# include "exec.h"
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
# define ERR_SYNTAX "Syntax error"

extern int	g_exit_flag;

int			create_env(t_env **env, char **envp);
void		free_env(t_env **env);
void		print_env(const t_env *env);
int			get_input(char **user_input);
void		cleanup_user_input(char **user_input);
void		set_up_var(t_var *var);
void		free_var(t_var *var);
int			set_and_return_code(t_var *var, int code);
void		setup_signal_handlers(void);
void		handle_sigint(int sig, siginfo_t *info, void *context);
void		handle_sigquit(int sig, siginfo_t *info, void *context);
void		handle_eof(void);

// t_env
char		*get_env_value(t_env *env, const char *key);
char		**get_path_from_env(t_env *env, int *error);

//t_iofile
t_iofile	*new_iofile(t_iotype type, const char *value);
void		append_iofile(t_iofile **head, t_iofile *new);
const char	*iottostr(t_iotype type);
void		free_iofile(t_iofile **io);

//t_tree_utils
size_t		token_word_count(t_token *tokens);
void		append_to_tree(t_tree **head, t_tree *new);
t_tree		*create_new_tree_node(t_token *tokens);
void		print_tree(t_tree *tree);
void		free_tree(t_tree **tree);

//t_tree
int			create_tree(t_tree **tree, t_token *tokens);

char		*get_env_value(t_env *env, const char *key);
char		**get_path_from_env(t_env *env, int *error);
char		**linked_list_to_array(t_env *env);

// utils.c
void		*free_to_null(void *p);
int			mclose(int *fd);
int			error(t_var *var, const char *msg, int code);

#endif
