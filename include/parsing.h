/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:49:21 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/31 14:02:59 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

//checks.c
int		check_open_quotes(const char *rl);

//is_checks.c
int		is_operator(char c);
int		is_space_tab(char c);
int		is_quotes(char c);

#endif
