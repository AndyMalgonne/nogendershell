/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:16:43 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/06 15:48:41 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "minishell.h"

typedef enum s_token_type
{
	CMD,
	ARG,
	BACKGROUND,
	AND,
	OR,
	SEMICOLON,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	O_BRACKET,
	C_BRACKET,
	SQ_STRING,
	DQ_STRING,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//token_utils.c
t_token	*new_token(t_token_type type, const char *value);
void	append_token(t_token **head, t_token *new_token);

//token.c

//cmd_tokenizing.c
int		cmd_tokenizing(char **rl, t_token **head);

//op_tokenizing.c
int		op_tokenizing(char **rl, t_token **head);

//op_tokenizing_helper.c
t_token	*tokenize_rdin(char **rl);
t_token	*tokenize_rdout(char **rl);
t_token	*tokenize_pipe(char **rl);
t_token	*tokenize_and(char **rl);
t_token	*tokenize_scln(char **rl);

//string_tokenizing.c
int		tokenize_s_quote(char **rl, t_token **head);
int		tokenize_d_quote(char **rl, t_token **head);
int		string_tokenizing(char **rl, t_token **head);

#endif
