/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:59:16 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/24 18:20:06 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtin(t_fds *fds, int pip[2], t_tree *cmd)
{
	if (is_builtin(cmd))
	{
		launch_builtin(fds, pip, cmd);
		(mclose(&pip[0]), mclose(&pip[1]));
		return (1);
	}
	return (0);
}

bool	is_builtin(const t_tree *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (false);
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (true);
	return (false);
}

void	exec_builtin(const t_tree *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		bi_pwd();
}

int	redirect_output(t_fds *fds, const int pip[2], const t_tree *cmd)
{
	int	saved_stdout;

	saved_stdout = -1;
	if (fds->outfd > 1)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (dup2(fds->outfd, STDOUT_FILENO) == -1)
			return (-1);
		mclose(&fds->outfd);
	}
	else if (cmd->next)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (dup2(pip[1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (saved_stdout);
}

void	launch_builtin(t_fds *fds, int pip[2], t_tree *cmd)
{
	int	saved_stdout;

	if (io_files(cmd->io, fds) < 0)
		return ;
	saved_stdout = redirect_output(fds, pip, cmd);
	if (saved_stdout == -1)
		return ;
	exec_builtin(cmd);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		mclose(&saved_stdout);
	}
	if (!cmd->next && fds->prev_fd != -1)
	{
		mclose(&fds->prev_fd);
		fds->prev_fd = -1;
	}
}
