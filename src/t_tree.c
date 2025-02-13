/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:11:39 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/13 14:29:25 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_word_token(t_tree *new, t_token *tokens)
{
	size_t	i;

	i = 0;
	while (new->cmd[i])
		i++;
	new->cmd[i] = ft_strdup(tokens->value);
	if (!new->cmd[i])
		return (0);
	return (1);
}

static int	handle_io_token(t_tree *new, t_token **tokens)
{
	t_iofile	*new_io;
	t_iotype	type;

	new_io = NULL;
	if ((*tokens)->next->type == REDIR_IN)
		type = HEREDOC;
	else if ((*tokens)->next->type == REDIR_OUT)
		type = OUTFILE_APPEND;
	else if ((*tokens)->type == REDIR_IN)
		type = INFILE;
	else
		type = OUTFILE_TRUNC;
	if (type == HEREDOC || type == OUTFILE_APPEND)
		*tokens = (*tokens)->next;
	new_io = new_iofile(type, (*tokens)->next->value);
	if (!new_io)
		return (0);
	append_iofile(&new->io, new_io);
	*tokens = (*tokens)->next;
	return (1);
}

static int	process_token(t_tree **tree, t_tree **new, t_token **tokens)
{
	if (!*new)
	{
		*new = create_new_tree_node(*tokens);
		if (!*new)
			return (0);
	}
	if ((*tokens)->type == PIPE)
	{
		append_to_tree(tree, *new);
		*new = NULL;
	}
	else if (is_word((*tokens)->type))
	{
		if (!handle_word_token(*new, *tokens))
			return (0);
	}
	else
	{
		if (!handle_io_token(*new, tokens))
			return (0);
	}
	return (1);
}

int	create_tree(t_tree **tree, t_token *tokens)
{
	t_tree	*new;

	new = NULL;
	while (tokens)
	{
		if (!process_token(tree, &new, &tokens))
			return (0);
		tokens = tokens->next;
	}
	if (new)
		append_to_tree(tree, new);
	return (1);
}
