/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tokenizing_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:50:20 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/06 14:54:01 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*tokenize_rdin(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(REDIR_IN, ft_strdup(">")));
	else if (is_rdin((*rl)[1]) && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(REDIR_APPEND, ft_strdup(">>")));
	return (NULL);
}

static t_token	*tokenize_rdout(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(REDIR_OUT, ft_strdup("<")));
	else if (is_rdout((*rl)[1]) && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(REDIR_HEREDOC, ft_strdup("<<")));
	return (NULL);
}

static t_token	*tokenize_pipe(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(PIPE, ft_strdup("|")));
	else if (is_pipe((*rl)[1]) && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(OR, ft_strdup("||")));
	return (NULL);
}

static t_token	*tokenize_and(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(BACKGROUND, ft_strdup("&")));
	else if (is_and((*rl)[1]) && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(AND, ft_strdup("&&")));
	return (NULL);
}

static t_token	*tokenize_scln(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(SEMICOLON, ft_strdup(";")));
	return (NULL);
}
