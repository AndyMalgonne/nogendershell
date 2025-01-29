/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:47:30 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/21 00:03:48 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_token_error(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (current->type == OP_SEMICOLON || current->type == OP_BACKLASH \
		|| current->type == SUBSHELL)
		{
			fprintf(stderr, ">nogendershell: Error: Unsupported token type: ");
			fprintf(stderr, "%s\n", tttostr(current->type));
			free_token_list(head);
			return ;
		}
		current = current->next;
	}
}
