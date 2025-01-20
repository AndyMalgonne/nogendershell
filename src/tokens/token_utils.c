/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:22 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/20 23:23:44 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, const char *value)
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
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}

void	free_token_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
	*head = NULL;
}

const char *tttostr(t_token_type type) //TO FIX, SWITCHCASE NOT ALLOWED
{
	switch (type)
	{
		case BI_ECHO: return "BI_ECHO";
		case BI_CD: return "BI_CD";
		case BI_PWD: return "BI_PWD";
		case BI_EXPORT: return "BI_EXPORT";
		case BI_UNSET: return "BI_UNSET";
		case BI_ENV: return "BI_ENV";
		case BI_EXIT: return "BI_EXIT";
		case OP_BACKGROUND: return "OP_BACKGROUND";
		case OP_AND: return "OP_AND";
		case OP_OR: return "OP_OR";
		case OP_SEMICOLON: return "OP_SEMICOLON";
		case OP_PIPE: return "OP_PIPE";
		case OP_REDIR_IN: return "OP_REDIR_IN";
		case OP_REDIR_OUT: return "OP_REDIR_OUT";
		case OP_REDIR_APPEND: return "OP_REDIR_APPEND";
		case OP_REDIR_HEREDOC: return "OP_REDIR_HEREDOC";
		case OP_BACKLASH: return "OP_BACKLASH";
		case STRING_SQ: return "STRING_SQ";
		case STRING_DQ: return "STRING_DQ";
		case SUBSHELL: return "SUBSHELL";
		default: return "UNKNOWN";
	}
}

void	print_token_list(t_token *head) //TO COMMENT
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("Type: %s, Value: %s\n", tttostr(current->type), current->value);
		current = current->next;
	}
}
