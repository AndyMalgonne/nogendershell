/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:22 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/30 14:06:33 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	tokenize_else(char **rl, t_token **head)
{
	t_token		*n_token;
	const char	*start;

	start = *rl;
	while (**rl && !is_space_tab(**rl))
		(*rl)++;
	n_token = new_token(WORD, ft_strndup(start, *rl - start));
	if (!n_token)
		return (0);
	append_token(head, n_token);
	return (2);
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	char	*rl;

	head = NULL;
	rl = input;
	if (check_open_quotes(rl) == 1 || check_open_brackets(rl) == 1)
		return (NULL);
	while (*rl)
	{
		while (is_space_tab(*rl))
			rl++;
		if (is_operator(*rl))
			op_tokenizing(&rl, &head);
		else if (is_quotes(*rl))
			string_tokenizing(&rl, &head);
		else if (is_cmd(rl))
			cmd_tokenizing(&rl, &head);
		else if (is_o_bracket(*rl))
			subshell_tokenizing(&rl, &head);
		else if (*rl)
			tokenize_else(&rl, &head);
	}
	return (head);
}
