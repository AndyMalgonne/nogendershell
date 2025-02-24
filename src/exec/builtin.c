/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:59:16 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/24 17:40:37 by amalgonn         ###   ########.fr       */
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
	(void)var;
    if (io_files(cmd->io, fds) < 0)
		return;
    int saved_stdout = -1;
    if (fds->outfd > 1)
    {
        saved_stdout = dup(STDOUT_FILENO);
        if (dup2(fds->outfd, STDOUT_FILENO) == -1)
			return ;
        mclose(&fds->outfd);
    }
    else if (cmd->next)
    {
        saved_stdout = dup(STDOUT_FILENO);
        if (dup2(pip[1], STDOUT_FILENO) == -1)
			return ;
    }
    exec_builtin(cmd);
    if (saved_stdout != -1)
    {
        dup2(saved_stdout, STDOUT_FILENO);
        mclose(&saved_stdout);
    }
}
