/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:14:54 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/28 10:22:37 by amalgonn         ###   ########.fr       */
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
		else if (tokens->type == PIPE && (!tokens->next \
		|| !tokens->prev || !is_word(tokens->prev->type)))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

static int	set_varcode_and_return(t_var *var, int code, int ret_code)
{
	var->code = code;
	return (ret_code);
}

int	parse_input(char *user_input, t_tree **tree, t_var *var)
{
	t_token *tokens	__attribute__((cleanup(free_token_list)));

	tokens = NULL;
	if (!check_open_quotes(user_input))
		return (set_and_return_code(var, 1));
	if (!tokenize(user_input, &tokens))
		return (ft_putendl_fd(ERR_MALLOC, 2),
			set_varcode_and_return(var, 1, 0));
	if (!expand(tokens, var))
		return (ft_putendl_fd(ERR_MALLOC, 2),
			set_varcode_and_return(var, 1, 0));
	if (!check_tokens(tokens))
		return (ft_putendl_fd(ERR_SYNTAX, 2),
			set_and_return_code(var, 1));
	if (!create_tree(tree, tokens))
		return (ft_putendl_fd(ERR_MALLOC, 2),
			set_varcode_and_return(var, 1, 0));
	return (1);
}
