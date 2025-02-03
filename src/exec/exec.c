/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/03 09:13:01 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	exec_cmd(t_tree *tree)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		(perror("fork"), exit(EXIT_FAILURE));
	else if (pid == 0)
	{
		if (tree->cmd && tree->cmd[0])
			child_process(tree);
	}
	else
		parent_process(tree);
	return (true);
}
