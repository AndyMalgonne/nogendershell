/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenizing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:33:45 by gmoulin           #+#    #+#             */
/*   Updated: 2024/10/31 20:12:53 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_single_quote(char **rl, t_token **head)
{
	t_token	*n_token;
	char	*start;

	(*rl)++;
	start = *rl;
	while (**rl && !is_squote(**rl))
		(*rl)++;
	n_token = new_token(SQ_STRING, ft_strndup(start, *rl - start));
	if (!n_token)
		return (0);
	append_token(head, n_token);
	if (**rl == '\'')
		(*rl)++;
	return (1);
}

int	tokenize_double_quote(char **rl, t_token **head)
{
	t_token		*n_token;
	const char	*start;

	(*rl)++;
	start = *rl;
	while (**rl && !is_dquote(**rl))
		(*rl)++;
	n_token = new_token(DQ_STRING, ft_strndup(start, rl - start));
	if (!n_token)
		return (0);
	append_token(head, n_token);
	if (**rl == '\"')
		(*rl)++;
	return (2);
}

int	string_tokenizing(char **rl, t_token **head)
{
	if (is_squote(*rl))
		return (tokenize_single_quote(rl, head));
	else if (is_dquote(*rl))
		return (tokenize_double_quote(rl, head));
	return (0);
}
