/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:22 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/27 21:10:00 by gmoulin          ###   ########.fr       */
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

const char	*tttostr(t_token_type type)
{
	static const char	*token_type_str[] = {
		"BI_ECHO", "BI_CD", "BI_PWD", "BI_EXPORT", "BI_UNSET",
		"BI_ENV", "BI_EXIT", "OP_BACKGROUND", "OP_AND", "OP_OR",
		"OP_SEMICOLON", "OP_PIPE", "OP_REDIR_IN", "OP_REDIR_OUT",
		"OP_REDIR_APPEND", "OP_REDIR_HEREDOC", "OP_BACKLASH",
		"STRING_SQ", "STRING_DQ", "SUBSHELL", "UNKNOWN"
	};

	if (type < 0 || type >= sizeof(token_type_str) / sizeof(token_type_str[0]))
		return ("UNKNOWN");
	return (token_type_str[type]);
}

//void	print_token_list(t_token *head) //TO COMMENT
//{
//	t_token	*current;

//	current = head;
//	while (current)
//	{
//		printf("Type: %s, Value: %s\n", tttostr(current->type), current->value);
//		current = current->next;
//	}
//}
