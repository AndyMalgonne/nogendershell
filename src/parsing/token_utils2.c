/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:37:32 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/11 20:14:02 by gmoulin          ###   ########.fr       */
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
