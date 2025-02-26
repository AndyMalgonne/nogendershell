/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:52:15 by amalgonn          #+#    #+#             */
/*   Updated: 2025/02/26 09:24:37 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_children(int pid)
{
	int	wstatus;
	int	code;

	wstatus = 0;
	code = 0;
	while (errno != ECHILD)
	{
		if (wait(&wstatus) == pid)
		{
			if (WIFEXITED(wstatus))
				code = WEXITSTATUS(wstatus);
			else
				code = 128 + WTERMSIG(wstatus);
		}
	}
	if (pid == -1)
		return (127);
	return (code);
}

void	init_and_reset_pipes(int pip[2])
{
	pip[0] = -1;
	pip[1] = -1;
}

void	init_fds_and_pid(t_fds *fds)
{
	fds->prev_fd = -1;
	fds->infd = 0;
	fds->outfd = 1;
	fds->heredocfd = -1;
	fds->pid = 0;
}
