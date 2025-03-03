/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:37:32 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/27 16:02:45 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*tttostr(t_token_type type)
{
	static const char	*token_type_str[] = {
		"PIPE",
		"REDIR_IN",
		"REDIR_OUT",
		"STRING_SQ",
		"STRING_DQ",
		"WORD",
	};

	if (type < 0 || type >= sizeof(token_type_str) / sizeof(token_type_str[0]))
		return ("WORD");
	return (token_type_str[type]);
}

void	print_token_list(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("Type: %s, Value: %s\n", tttostr(current->type), current->value);
		current = current->next;
	}
}

bool	is_word(t_token_type type)
{
	return (type == WORD || type == STRING_SQ || type == STRING_DQ);
}

int	handle_quotes(char **rl, char **value)
{
	char		quote_char;
	const char	*start;

	while (**rl && is_quotes(**rl))
	{
		quote_char = **rl;
		(*rl)++;
		start = *rl;
		while (**rl && **rl != quote_char)
			(*rl)++;
		*value = ft_strnjoin(*value, start, *rl - start);
		if (!*value)
			return (0);
		if (**rl == quote_char)
			(*rl)++;
	}
	return (1);
}
