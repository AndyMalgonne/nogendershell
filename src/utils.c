/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:02:20 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/25 20:50:13 by gmoulin          ###   ########.fr       */
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
	if (*fd != -1 && *fd != STDIN_FILENO
		&& *fd != STDOUT_FILENO && *fd != STDERR_FILENO)
	{
		close(*fd);
		*fd = -1;
	}
	return (1);
}

int	error(t_var *var, const char *msg, int code)
{
	if (msg)
	{
		ft_putstr_fd((char *)msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (var)
		var->code = code;
	return (0);
}

void	free_all(t_tree *tree, t_var *var)
{
	free_tree(&tree);
	free_var(var);
	rl_clear_history();
}
