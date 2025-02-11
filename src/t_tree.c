/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:11:39 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/11 21:48:22 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	token_word_count(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (is_word(tokens->type))
			++count;
		tokens = tokens->next;
	}
	return (count);
}

static void	append_to_tree(t_tree **head, t_tree *new)
{
	t_tree	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	create_tree(t_tree **tree, t_token *tokens)
{
	t_tree	*new;
	size_t	i;

	new = NULL;
	while (tokens)
	{
		if (!new)
		{
			new = ft_calloc(1, sizeof(t_tree));
			if (!new)
				return (0);
			new->cmd = ft_calloc(token_word_count(tokens) + 1, sizeof(char *));
			if (!new->cmd)
				return (0);
			new->next = NULL;
		}
		if (tokens->type == PIPE)
			(append_to_tree(tree, new), new = NULL);
		else if (is_word(tokens->type))
		{
			i = 0;
			while (new->cmd[i])
				i++;
			new->cmd[i] = ft_strdup(tokens->value);
			if (!new->cmd[i])
				return (0);
		}
		else
		{
			t_iofile	*new_io;
			t_iotype	type;

			new_io = NULL;
			if (tokens->next->type == REDIR_IN)
				type = HEREDOC;
			else if (tokens->next->type == REDIR_OUT)
				type = OUTFILE_APPEND;
			else if (tokens->type == REDIR_IN)
				type = INFILE;
			else
				type = OUTFILE_TRUNC;
			if (type == HEREDOC || type == OUTFILE_APPEND)
				tokens = tokens->next;
			new_io = new_iofile(type, tokens->next->value);
			if (!new_io)
				return (0);
			append_iofile(&new->io, new_io);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	if (new)
		(append_to_tree(tree, new), new = NULL);
	return (1);
}
