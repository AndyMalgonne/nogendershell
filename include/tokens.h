/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:16:43 by gmoulin           #+#    #+#             */
/*   Updated: 2024/10/31 19:38:49 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

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
	SQ_STRING,
	DQ_STRING,
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

//tonken_utils.c
t_token	*new_token(t_token_type type, char *value);
void	append_token(t_token **head, t_token *new_token);

#endif
