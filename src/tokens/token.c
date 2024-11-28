/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:22 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/28 17:12:09 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_else(char **rl, t_token **head)
{
	t_token		*n_token;
	const char	*start;

	start = *rl;
	while (**rl && !is_space_tab(**rl))
		(*rl)++;
	n_token = new_token(UNKNOWN, ft_strndup(start, *rl - start));
	if (!n_token)
		return (0);
	append_token(head, n_token);
	return (2);
}

t_token *tokenize(char *input)
{
	t_token *head = NULL;
	char *rl = input;

	while (*rl)
	{
		if (is_space_tab(*rl))
		{
			rl++;
			continue;
		}
		if (is_operator(*rl))
		{
			op_tokenizing(&rl, &head);
			while (is_space_tab(*rl))
				rl++;
			continue;
		}
		if (is_quotes(*rl))
		{
			string_tokenizing(&rl, &head);
			while (is_space_tab(*rl))
				rl++;
			continue;
		}
		cmd_tokenizing(&rl, &head);
		if (*rl && !is_space_tab(*rl))
			tokenize_else(&rl, &head);
	}
	return head;
}
