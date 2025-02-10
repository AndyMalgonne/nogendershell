/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:14:54 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/04 14:56:58 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(char *user_input, t_tree **tree, t_var *var)
{
	t_token *tokens	__attribute__((cleanup(free_token_list)));

	(void)tree;
	tokens = NULL;
	if (!check_open_quotes(user_input))
		return (set_and_return_code(var, 1));
	if (!tokenize(user_input, &tokens))
		return (error(var, "Malloc error", 1));
	if (!expand(tokens, var->env))
		return (error(var, "Malloc error", 1));
	return (1);
}
