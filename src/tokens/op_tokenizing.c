/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tokenizing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:14:57 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/31 14:20:37 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_rdin(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(REDIR_IN, ft_strdup(">")));
	else if ((*rl)[1] == '<' && (is_space_tab((*rl)[2]) || !(*rl)[2]))
		return (new_token(REDIR_APPEND, ft_strdup(">>")));
	return (NULL);
}

t_token	*tokenize_rdout(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(REDIR_OUT, ft_strdup("<")));
	else if ((*rl)[1] == '>' && (is_space_tab((*rl)[2]) || !(*rl)[2]))
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
	if (**rl == '<')
		n_token = tokenize_rdin(rl);
	else if (**rl == '>')
		n_token = tokenize_rdout(rl);
	else if (**rl == '|')
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
