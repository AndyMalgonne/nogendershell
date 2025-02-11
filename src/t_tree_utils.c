/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:41:00 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/11 21:42:54 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
