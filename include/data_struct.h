/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:17:26 by abasdere          #+#    #+#             */
/*   Updated: 2025/01/31 14:18:28 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

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

#endif
