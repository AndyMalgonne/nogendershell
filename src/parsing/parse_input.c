/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:14:54 by abasdere          #+#    #+#             */
/*   Updated: 2025/01/31 16:04:00 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(char *user_input, t_tree **tree, const t_env *env)
{
	t_token *tokens	__attribute__((cleanup(free_token_list)));

	(void)tree;
	(void)env;
	tokens = NULL;
	if (!check_open_quotes(user_input))
		return (1);
	if (!tokenize(user_input, &tokens))
		return (printf("test\n"), 0);
	print_token_list(tokens);
	return (1);
}
