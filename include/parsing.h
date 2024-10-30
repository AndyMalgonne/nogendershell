/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:49:21 by gmoulin           #+#    #+#             */
/*   Updated: 2024/10/24 16:32:21 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum s_token_type
{
	WORD,
	AND,
	OR,
	PIPE,
	SEMICOLON,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	O_BRACKET,
	C_BRACKET,
	N_LINE,
	END,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

#endif
