/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:59:16 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/26 13:46:37 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtin(const t_tree *cmd)
{
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (false);
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (true);
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (true);
	if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (true);
	if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (true);
	return (false);
}

static void	exec_builtin(const t_tree *cmd, t_var *env, t_fds *fds)
{
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		bi_pwd(cmd, env);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		bi_env(cmd, env);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		bi_echo(cmd->cmd, env);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		bi_exit(cmd, env, fds);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		bi_export(cmd, env);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		bi_unset(cmd->cmd, &env);
}

int	handle_builtin(t_fds *fds, int pip[2], t_tree *cmd, t_var *env)
{
	if (is_builtin(cmd))
	{
		launch_builtin(fds, pip, cmd, env);
		(mclose(&pip[0]), mclose(&pip[1]));
		return (1);
	}
	return (0);
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

void	launch_builtin(t_fds *fds, const int pip[2], t_tree *cmd, t_var *env)
{
	int	saved_stdout;

	if (io_files(cmd->io, fds) < 0)
		return ;
	saved_stdout = redirect_output(fds, pip, cmd);
	exec_builtin(cmd, env, fds);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		mclose(&saved_stdout);
	}
	if (!cmd->next && fds->prev_fd != -1)
		mclose(&fds->prev_fd);
	(mclose(&fds->infd), fds->infd = 0);
	(mclose(&fds->outfd), fds->outfd = 1);
}
