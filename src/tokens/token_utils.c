/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:19:22 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/31 14:21:54 by abasdere         ###   ########.fr       */
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
		"PIPE",
		"REDIR_IN",
		"REDIR_OUT",
		"REDIR_APPEND",
		"REDIR_HEREDOC",
		"STRING_SQ",
		"STRING_DQ",
		"WORD",
	};

	if (type < 0 || type >= sizeof(token_type_str) / sizeof(token_type_str[0]))
		return ("WORD");
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
