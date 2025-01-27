/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tokenizing_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:50:20 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/27 20:16:14 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_rdin(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(OP_REDIR_IN, ft_strdup(">")));
	else if (is_rdin((*rl)[1]) && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(OP_REDIR_APPEND, ft_strdup(">>")));
	return (NULL);
}

t_token	*tokenize_rdout(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(OP_REDIR_OUT, ft_strdup("<")));
	else if (is_rdout((*rl)[1]) && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(OP_REDIR_HEREDOC, ft_strdup("<<")));
	return (NULL);
}

t_token	*tokenize_pipe(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(OP_PIPE, ft_strdup("|")));
	else if (is_pipe((*rl)[1]) && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(OP_OR, ft_strdup("||")));
	return (NULL);
}

t_token	*tokenize_and(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(OP_BACKGROUND, ft_strdup("&")));
	else if (is_and((*rl)[1]) && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(OP_AND, ft_strdup("&&")));
	return (NULL);
}

t_token	*tokenize_scln(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(OP_SEMICOLON, ft_strdup(";")));
	return (NULL);
}
