/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:33:38 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/01/30 13:14:46 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <curses.h>
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

# define PROMPT "> "
# define ERR_MALLOC "Malloc error"

typedef enum e_iotype
{
	INFILE,
	HEREDOC,
	OUTFILE_TRUNC,
	OUTFILE_APPEND,
}					t_iotype;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_iofile
{
	t_iotype		type;
	char			*value;
	struct s_iofile	*next;
}					t_iofile;

typedef struct s_tree
{
	char			**cmd;
	t_iofile		*io;
	struct s_tree	*next;
}					t_tree;

extern int			g_signal;

void	*free_to_null(void *p);
int		create_env(t_env **env, char **envp);
void	free_env(t_env **env);
int		get_input(char **user_input);
void	cleanup_user_input(char **user_input);

#endif
