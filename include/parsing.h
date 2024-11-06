/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:49:21 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/06 16:55:23 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

//checks.c
int		check_open_quotes(const char *rl);
int		check_open_brackets(const char *rl);

//bracket_checks.c
int		is_o_bracket(char c);
int		is_c_bracket(char c);

//op_checks.c
int		is_rdin(char c);
int		is_rdout(char c);
int		is_pipe(char c);
int		is_scln(char c);
int		is_and(char c);

//quotes_checks.c
int		is_quotes(char c);
int		is_s_quote(char c);
int		is_d_quote(char c);

//is_checks.c
int		is_operator(char c);
int		is_space_tab(char c);
int		is_cmd(char *rl);

//is_check_helper.c
int		is_builtin1(char *rl);
int		is_builtin2(char *rl);
int		is_builtin3(char *rl);

//parsing.c
char	*parsing(char *rl, t_token **head);

//cmd_checks.c
int		is_bi_echo(const char *rl);
int		is_bi_cd(const char *rl);
int		is_bi_pwd(const char *rl);
int		is_bi_export(const char *rl);
int		is_bi_unset(const char *rl);

//cmd_checks2.c
int		is_bi_env(const char *rl);
int		is_bi_exit(const char *rl);

#endif
