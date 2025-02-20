/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:22 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/20 00:31:39 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenize_else(char **rl, t_token **head)
{
	t_token		*n_token;
	char		*start;

	start = *rl;
	while (**rl && !is_space_tab(**rl) && !is_operator(**rl))
		(*rl)++;
	start = ft_strndup(start, *rl - start);
	if (!start)
		return (0);
	n_token = new_token(WORD, start);
	if (!n_token)
		return (free(start), 0);
	append_token(head, n_token);
	return (free(start), 1);
}

static int	string_tokenizing(char **rl, t_token **head)
{
	t_token_type	type;
	t_token			*n_token;
	char			*start;

	start = (*rl)++;
	type = STRING_SQ;
	if (*start == '\"')
		type = STRING_DQ;
	while (**rl && **rl != *start)
		(*rl)++;
	if (**rl == *start)
		(*rl)++;
	start = ft_strndup(start + 1, *rl - start - 2);
	if (!start)
		return (0);
	n_token = new_token(type, start);
	if (!n_token)
		return (free(start), 0);
	append_token(head, n_token);
	return (free(start), 1);
}

static int	op_tokenizing(char **rl, t_token **head)
{
	t_token	*n_token;

	n_token = NULL;
	if (**rl == '<')
		n_token = new_token(REDIR_IN, NULL);
	else if (**rl == '>')
		n_token = new_token(REDIR_OUT, NULL);
	else if (**rl == '|')
		n_token = new_token(PIPE, NULL);
	if (!n_token)
		return (0);
	append_token(head, n_token);
	(*rl)++;
	return (1);
}

int	tokenize(char *input, t_token **head)
{
	while (*input)
	{
		while (is_space_tab(*input))
			input++;
		if (is_operator(*input))
		{
			if (!op_tokenizing(&input, head))
				return (0);
		}
		else if (is_quotes(*input))
		{
			if (!string_tokenizing(&input, head))
				return (0);
		}
		else
		{
			if (!tokenize_else(&input, head))
				return (0);
		}
	}
	return (1);
}
