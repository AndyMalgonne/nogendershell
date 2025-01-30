/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:16:43 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/30 14:06:30 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum s_token_type
{
	OP_PIPE,
	OP_REDIR_IN,
	OP_REDIR_OUT,
	OP_REDIR_APPEND,
	OP_REDIR_HEREDOC,
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
const char	*tttostr(t_token_type type);
//void		print_token_list(t_token *head);

//token.c
t_token		*tokenize(char *input);

//cmd_tokenizing.c
int			cmd_tokenizing(char **rl, t_token **head);

//op_tokenizing.c
int			op_tokenizing(char **rl, t_token **head);

//op_tokenizing_helper.c
t_token		*tokenize_rdin(char **rl);
t_token		*tokenize_rdout(char **rl);
t_token		*tokenize_pipe(char **rl);
t_token		*tokenize_and(char **rl);
t_token		*tokenize_scln(char **rl);

//op_tokenizing_helper2.c
t_token		*tokenize_backlash(char **rl);

//string_tokenizing.c
int			tokenize_s_quote(char **rl, t_token **head);
int			tokenize_d_quote(char **rl, t_token **head);
int			string_tokenizing(char **rl, t_token **head);

//subshell_tokenizing.c
int			subshell_tokenizing(char **rl, t_token **head);

#endif
