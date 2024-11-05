/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokenizing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:14:57 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/05 16:29:10 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operator_tokenizing(char **rl, t_token **head)
{
	t_token	*n_token;

	if (is_rdin(**rl))
		if (is_rdin(**rl + 1))
			n_token = new_token(REDIR_APPEND, ft_strdup(">>"));
		else
			n_token = new_token(REDIR_IN, ft_strdup(">"));
	else if (is_rdout(**rl))
		if (is_rdout(**rl + 1))
			n_token = new_token(REDIR_HEREDOC, ft_strdup("<<"));
		else
			n_token = new_token(REDIR_OUT, ft_strdup("<"));
	else if (is_pipe(**rl))
		n_token = new_token(PIPE, ft_strdup("|"));
	else
		return (0);
	if (!n_token)
		return (0);
	append_token(head, n_token);
	while (**rl && !is_space_tab(**rl))
		(*rl)++;
	return (1);
}
