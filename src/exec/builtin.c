/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:59:16 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/21 20:37:00 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_tree *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (true);
	return (false);
}

void	exec_builtin(t_tree *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		bi_pwd();
}

void launch_builtin(t_fds *fds, int pip[2], t_tree *cmd, t_var *var)
{
    (void)pip;
    int saved_stdout = dup(STDOUT_FILENO);
    if (io_files(cmd->io, fds) < 0)
        (free_all(cmd, var), exit(1));
    if (fds->outfd > 1)
    {
        if (dup2(fds->outfd, STDOUT_FILENO) == -1)
            (close_fds(fds), free_all(cmd, var), exit(1));
        mclose(&(fds->outfd));
    }
    exec_builtin(cmd);
    if (saved_stdout != -1)
    {
        if (dup2(saved_stdout, STDOUT_FILENO) == -1)
            (close(saved_stdout), close_fds(fds), free_all(cmd, var), exit(1));
        mclose(&saved_stdout);
    }
}
