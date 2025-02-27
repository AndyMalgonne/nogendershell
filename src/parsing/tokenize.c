/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:22 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/27 17:12:01 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	handle_quotes_type(char **rl, char **value, t_token_type *type)
{
	if (**rl == '\'')
		*type = STRING_SQ;
	else
		*type = STRING_DQ;
	if (!handle_quotes(rl, value))
		return (free(*value), 0);
	return (1);
}

static int	process_rl(char **rl, char **value, t_token_type *type)
{
	while (**rl && !is_space_tab(**rl) && !is_operator(**rl))
	{
		if (is_quotes(**rl))
		{
			if (!handle_quotes_type(rl, value, type))
				return (0);
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
	t_token			*n_token;
	char			*value;
	t_token_type	type;

	value = ft_strdup("");
	if (!value)
		return (0);
	type = WORD;
	if (!process_rl(rl, &value, &type))
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
		else
		{
			if (!tokenize_else(&input, head))
				return (0);
		}
	}
	return (1);
}
