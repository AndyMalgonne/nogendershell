/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:16:43 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/31 15:45:50 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

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

//token_utils.c
t_token		*new_token(t_token_type type, const char *value);
void		append_token(t_token **head, t_token *new_token);
void		free_token(t_token *token);
void		free_token_list(t_token **head);

//token_utils2.c
void		print_token_list(t_token *head);
const char	*tttostr(t_token_type type);

//tokenize.c
int			tokenize(char *input, t_token **head);

int			parse_input(char *user_input, t_tree **tree, t_env *env);

#endif
