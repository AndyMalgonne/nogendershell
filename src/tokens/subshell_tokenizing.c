/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_tokenizing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:23:26 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/20 23:12:35 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	subshell_tokenizing(char **rl, t_token **head)
{
	t_token		*n_token;
	const char	*start;
	int			bracket_count;

	bracket_count = 1;
	start = *rl;
	(*rl)++;
	while (**rl && bracket_count > 0)
	{
		if (is_o_bracket(**rl))
			bracket_count++;
		else if (is_c_bracket(**rl))
			bracket_count--;
		(*rl)++;
	}
	n_token = new_token(SUBSHELL, ft_strndup(start, *rl - start));
	if (!n_token)
		return (0);
	append_token(head, n_token);
	return (1);
}
