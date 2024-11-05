/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:49:21 by gmoulin           #+#    #+#             */
/*   Updated: 2024/10/31 19:38:10 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

//checks.c
int		check_open_quotes(const char *rl);
int		check_open_brackets(const char *rl);

//bracket_checks.c
int		is_obracket(char c);
int		is_cbracket(char c);

//op_checks.c
int		is_rdin(char c);
int		is_rdout(char c);
int		is_pipe(char c);
int		is_scln(char c);
int		is_and(char c);

//quotes_checks.c
int		is_quotes(char c);
int		is_squote(char c);
int		is_dquote(char c);

//is_checks.c
int		is_operator(char c);
int		is_space_tab(char c);

//parsing.c
char	*parsing(char *rl, t_token **head);

//string_tokenizing.c
int		tokenize_single_quote(char **rl, t_token **head);
int		tokenize_double_quote(char **rl, t_token **head);
int		string_tokenizing(char **rl, t_token **head);

//operator_tokenizing.c
int		operator_tokenizing(char **rl, t_token **head);

#endif
