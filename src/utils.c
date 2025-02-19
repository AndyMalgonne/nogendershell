/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:02:20 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/19 14:27:30 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_to_null(void *p)
{
	void	**ptr;

	ptr = (void **)p;
	if (!ptr || !(*ptr))
		return (NULL);
	free(*ptr);
	*ptr = NULL;
	return (*ptr);
}

int	mclose(int *fd)
{
	if (*fd != -1 || *fd != 0 || *fd != 1 || *fd != 2)
	{
		close(*fd);
		*fd = -1;
	}
	return (1);
}

int	error(t_var *var, const char *msg, int code)
{
	if (msg)
		perror(msg);
	if (var)
		var->code = code;
	return (0);
}

void	free_all(t_tree *tree, t_var *var)
{
	free_tree(&tree);
	free_var(var);
}
