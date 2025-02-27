/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:17:26 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/27 20:01:19 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

typedef enum e_iotype
{
	INFILE,
	HEREDOC,
	HEREDOC_NO_EXPAND,
	OUTFILE_TRUNC,
	OUTFILE_APPEND,
}					t_iotype;

typedef struct s_env
{
	char			*key;
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

typedef struct s_var
{
	t_env			*env;
	int				code;
	t_tree			*head;
}					t_var;

#endif
