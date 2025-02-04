/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:14:54 by abasdere          #+#    #+#             */
/*   Updated: 2025/01/31 17:50:03 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(char *user_input, t_tree **tree, t_var *var)
{
	t_token *tokens	__attribute__((cleanup(free_token_list)));

	(void)tree;
	(void)var;
	tokens = NULL;
	if (!check_open_quotes(user_input))
		return (1);
	if (!tokenize(user_input, &tokens) && set_and_return_code(var, 1))
		return (0);
	print_token_list(tokens);
	return (1);
}
