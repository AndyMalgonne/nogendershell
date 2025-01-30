/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tokenizing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:14:57 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/30 16:33:20 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "parsing.h"

t_token	*tokenize_rdin(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(REDIR_IN, ft_strdup(">")));
	else if (is_rdin((*rl)[1]) && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(REDIR_APPEND, ft_strdup(">>")));
	return (NULL);
}

t_token	*tokenize_rdout(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(REDIR_OUT, ft_strdup("<")));
	else if (is_rdout((*rl)[1]) && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(REDIR_HEREDOC, ft_strdup("<<")));
	return (NULL);
}

t_token	*tokenize_pipe(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(PIPE, ft_strdup("|")));
	return (NULL);
}

int	op_tokenizing(char **rl, t_token **head)
{
	t_token	*n_token;

	n_token = NULL;
	if (is_rdin(**rl))
		n_token = tokenize_rdin(rl);
	else if (is_rdout(**rl))
		n_token = tokenize_rdout(rl);
	else if (is_pipe(**rl))
		n_token = tokenize_pipe(rl);
	else
		return (0);
	if (!n_token)
		return (0);
	append_token(head, n_token);
	while (**rl && !is_space_tab(**rl))
		(*rl)++;
	return (1);
}
