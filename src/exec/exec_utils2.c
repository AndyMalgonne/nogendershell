/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:09:54 by amalgonn          #+#    #+#             */
/*   Updated: 2025/02/26 19:03:18 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_tree *cmd, t_fds *fds, t_var *var)
{
	if (process_heredoc(cmd, fds, var) < 0)
	{
		close_fds(fds);
		return (error(var, "heredoc failed", 1));
	}
	return (0);
}

int	handle_builtin_next(t_fds *fds, int pip[2], t_tree **cmd, t_var *env)
{
	if (handle_builtin(fds, pip, *cmd, env))
	{
		*cmd = (*cmd)->next;
		return (1);
	}
	return (0);
}

int	handle_fork(t_fds *fds, int pip[2], t_tree *cmd, t_var *var)
{
	fds->pid = fork();
	if (fds->pid < 0)
		return (error(var, "fork failed", 1));
	if (fds->pid == 0)
		children_process(fds, pip, cmd, var);
	return (0);
}
