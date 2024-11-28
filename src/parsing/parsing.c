/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:15:01 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/28 16:02:30 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parsing(char *rl, t_token **head)
{
	char	*original_rl;

	original_rl = rl;
	if (check_open_quotes(rl) == 1 || check_open_brackets(rl) == 1)
		return (NULL);
	while (*rl)
	{
		if (is_space_tab(*rl) == 1)
			rl++;
		if (is_operator(*rl) == 1)
			op_tokenizing(&rl, head);
		else if (is_quotes(*rl) == 1)
			string_tokenizing(&rl, head);
		else
			rl++;
	}
	return (original_rl);
}
