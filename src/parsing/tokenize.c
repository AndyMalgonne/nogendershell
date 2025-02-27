/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:22 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/27 13:28:04 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	process_token(char **rl, char **value)
{
	while (**rl && !is_space_tab(**rl) && !is_operator(**rl))
	{
		if (is_quotes(**rl))
		{
			char quote_char = **rl;
			(*rl)++;
			char *start = *rl;
			while (**rl && **rl != quote_char)
				(*rl)++;
			*value = ft_strnjoin(*value, start, *rl - start);
			if (!*value)
				return (0);
			if (**rl == quote_char)
				(*rl)++;
		}
		else
		{
			*value = ft_strnjoin(*value, *rl, 1);
			if (!*value)
				return (0);
			(*rl)++;
		}
	}
	return (1);
}

static int	tokenize_else(char **rl, t_token **head)
{
	t_token		*n_token;
	char		*value;

	value = ft_strdup("");
	if (!value)
		return (0);
	if (!process_token(rl, &value))
		return (free(value), 0);
	n_token = new_token(WORD, value);
	if (!n_token)
		return (free(value), 0);
	append_token(head, n_token);
	return (free(value), 1);
}

static int	string_tokenizing(char **rl, t_token **head)
{
	t_token_type	type;
	t_token			*n_token;
	const char		*start;
	char			*value;

	start = (*rl)++;
	type = STRING_SQ;
	if (*start == '\"')
		type = STRING_DQ;
	while (**rl && **rl != *start)
		(*rl)++;
	if (**rl == *start)
		(*rl)++;
	if (*rl - start - 2 == 0)
		value = ft_strdup("");
	else
		value = ft_strndup(start + 1, *rl - start - 2);
	if (!value)
		return (0);
	n_token = new_token(type, value);
	if (!n_token)
		return (free(value), 0);
	append_token(head, n_token);
	return (free(value), 1);
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
