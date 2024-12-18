/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tokenizing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:14:57 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/06 15:26:49 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (is_and(**rl))
		n_token = tokenize_and(rl);
	else if (is_scln(**rl))
		n_token = tokenize_scln(rl);
	else
		return (0);
	if (!n_token)
		return (0);
	append_token(head, n_token);
	while (**rl && !is_space_tab(**rl))
		(*rl)++;
	return (1);
}
