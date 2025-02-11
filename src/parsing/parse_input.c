/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:14:54 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/11 20:05:17 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT)
		{
			if (tokens->next && tokens->type == tokens->next->type
				&& tokens->next->next && is_word(tokens->next->next->type))
			{
				tokens = tokens->next;
			}
			else if (!tokens->next || !is_word(tokens->next->type))
				return (0);
		}
		else if (tokens->type == PIPE)
		{
			if (!tokens->next
				|| !tokens->prev || !is_word(tokens->prev->type))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	parse_input(char *user_input, t_tree **tree, t_var *var)
{
	t_token *tokens	__attribute__((cleanup(free_token_list)));

	(void)tree;
	tokens = NULL;
	if (!check_open_quotes(user_input))
		return (set_and_return_code(var, 1));
	if (!tokenize(user_input, &tokens))
		return (error(var, ERR_MALLOC, 1));
	if (!expand(tokens, var->env))
		return (error(var, ERR_MALLOC, 1));
	if (!check_tokens(tokens))
		return (error(var, ERR_SYNTAX, 1), 1);
	if (!create_tree(tree, tokens))
		return (error(var, ERR_MALLOC, 1));
	return (1);
}
