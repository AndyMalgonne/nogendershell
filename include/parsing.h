/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:49:21 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/30 14:18:41 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//checks.c
int		check_open_quotes(const char *rl);
int		check_open_brackets(const char *rl);

//quotes_checks.c
int		is_quotes(char c);

//is_checks.c
int		is_operator(char c);
int		is_space_tab(char c);

#endif
