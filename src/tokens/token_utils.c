/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:22 by gmoulin           #+#    #+#             */
/*   Updated: 2024/10/31 18:19:45 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = strdup(value);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->prev = tmp;
}

void	free_token(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}
