/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokenizing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:14:57 by gmoulin           #+#    #+#             */
/*   Updated: 2024/10/31 19:10:39 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operator_tokenizing(char **rl, t_token **head)
{
	t_token	*n_token;

	n_token = new_token(WORD, ft_strdup(*rl));
	if (!n_token)
		return (0);
	if (is_redir_in(**rl))
		n_token->type = REDIR_IN;
	else if (is_redir_out(**rl))
		n_token->type = REDIR_OUT;
	else if (is_pipe(**rl))
		n_token->type = PIPE;
	else if (is_semicolon(**rl))
		n_token->type = SEMICOLON;
	else if (is_and(**rl))
		n_token->type = AND;
	else
		return (0);
	append_token(head, n_token);
	(*rl)++;
	return (1);
}
