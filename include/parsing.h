/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:49:21 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/27 13:54:05 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <stddef.h>

# include "data_struct.h"

# define CHAR_ERROR "`(){}[];!\\*"

typedef enum s_token_type
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	STRING_SQ,
	STRING_DQ,
	WORD,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_quote_status
{
	size_t	double_quote;
	size_t	single_quote;
	bool	inside_double_quote;
	bool	inside_single_quote;
}	t_quote_status;

//token_utils.c
t_token		*new_token(t_token_type type, const char *value);
void		append_token(t_token **head, t_token *new_token);
void		free_token(t_token *token);
void		free_token_list(t_token **head);

//token_utils2.c
void		print_token_list(t_token *head);
const char	*tttostr(t_token_type type);
bool		is_word(t_token_type type);
int			handle_quotes(char **rl, char **value);

//tokenize.c
int			tokenize(char *input, t_token **head);
int			parse_input(char *user_input, t_tree **tree, t_var *var);

//checks.c
int			check_open_quotes(const char *rl);

//is_checks.c
int			is_operator(char c);
int			is_space_tab(char c);
int			is_quotes(char c);

//expand.c
int			expand(t_token *tokens, const t_var *var);

#endif
