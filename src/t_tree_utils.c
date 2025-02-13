/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:41:00 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/13 14:27:11 by gmoulin          ###   ########.fr       */
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

void	append_to_tree(t_tree **head, t_tree *new)
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

t_tree	*create_new_tree_node(t_token *tokens)
{
	t_tree	*new;

	new = ft_calloc(1, sizeof(t_tree));
	if (!new)
		return (NULL);
	new->cmd = ft_calloc(token_word_count(tokens) + 1, sizeof(char *));
	if (!new->cmd)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	print_tree(t_tree *tree)
{
	size_t		i;
	t_iofile	*tmp;

	while (tree)
	{
		printf("NODE:\n\tCMD:");
		if (tree->cmd)
		{
			i = 0;
			while (tree->cmd[i])
				printf(" %s", tree->cmd[i++]);
		}
		printf("\n\tIO:");
		tmp = tree->io;
		while (tmp)
		{
			printf(" Type: %s, Value: %s", iottostr(tmp->type), tmp->value);
			tmp = tmp->next;
		}
		printf("\n");
		tree = tree->next;
	}
}

void	free_tree(t_tree **tree)
{
	if (*tree)
	{
		if ((*tree)->cmd)
			ft_fsplit((*tree)->cmd);
		free_iofile(&(*tree)->io);
		free_tree(&(*tree)->next);
		free_to_null(tree);
	}
}
