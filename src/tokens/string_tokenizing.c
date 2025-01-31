/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenizing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:33:45 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/31 14:21:49 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_s_quote(char **rl, t_token **head)
{
	t_token		*n_token;
	const char	*start;

	start = *rl;
	(*rl)++;
	while (**rl && **rl != '\'')
		(*rl)++;
	if (**rl == '\'')
		(*rl)++;
	n_token = new_token(STRING_SQ, ft_strndup(start, *rl - start));
	if (!n_token)
		return (0);
	append_token(head, n_token);
	return (1);
}

int	tokenize_d_quote(char **rl, t_token **head)
{
	t_token		*n_token;
	const char	*start;

	start = *rl;
	(*rl)++;
	while (**rl && **rl != '\"')
		(*rl)++;
	if (**rl == '\"')
		(*rl)++;
	n_token = new_token(STRING_DQ, ft_strndup(start, *rl - start));
	if (!n_token)
		return (0);
	append_token(head, n_token);
	return (2);
}

int	string_tokenizing(char **rl, t_token **head)
{
	if (**rl == '\'')
		return (tokenize_s_quote(rl, head));
	else if (**rl == '\"')
		return (tokenize_d_quote(rl, head));
	return (0);
}
