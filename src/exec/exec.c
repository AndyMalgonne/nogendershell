/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/25 10:21:18 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(const t_tree *cmd, t_var *var)
{
	char	**env_array;
	char	*full_cmd;

	env_array = linked_list_to_array(var->env);
	if (!env_array)
		(perror("Malloc failed"), free_all(var->head, var), exit(1));
	full_cmd = find_file(cmd->cmd[0], var);
	if (!full_cmd)
		(ft_fsplit(env_array), free_all(var->head, var), exit(127));
	if (execve(full_cmd, cmd->cmd, env_array) == -1)
		(perror("execve failed"), free(full_cmd), ft_fsplit(env_array),
			free_all(var->head, var), exit(1));
	exit(0);
}

void	children_process(t_fds *fds, int pip[2], t_tree *cmd, t_var *var)
{
	if (io_files(cmd->io, fds) < 0)
		(mclose(&pip[0]), mclose(&pip[1]), free_all(var->head, var), exit(1));
	redir(fds, pip, cmd, var);
	exec_cmd(cmd, var);
}

void	init_fds_and_pid(t_fds *fds, pid_t *pid)
{
	fds->prev_fd = -1;
	fds->infd = 0;
	fds->outfd = 1;
	fds->heredocfd = -1;
	*pid = 0;
}

void	parent_process(t_fds *fds, int pip[2], const t_tree *cmd)
{
	if (fds->prev_fd != -1)
	{
		mclose(&fds->heredocfd);
		mclose(&(fds->prev_fd));
	}
	if (cmd->next)
	{
		fds->prev_fd = pip[0];
		mclose(&pip[1]);
	}
	else
		(mclose(&pip[0]), mclose(&pip[1]), mclose(&fds->heredocfd));
}

static int process_heredoc(t_tree *cmd, t_fds *fds)
{
    t_iofile *io;

    io = cmd->io;
    while (io)
    {
        if (io->type == HEREDOC)
        {
            if (fds->heredocfd > 0)
                mclose(&(fds->heredocfd));
            fds->heredocfd = get_here_doc(io->value);
            if (fds->heredocfd < 0)
                return (mclose(&fds->heredocfd), -1);
        }
        io = io->next;
    }
    return (0);
}

int	minishell_exec(t_tree *cmd, t_var *var)
{
	int		pip[2];
	t_fds	fds;
	pid_t	pid;

	init_fds_and_pid(&fds, &pid);
	while (cmd)
	{
		init_and_reset_pipes(pip);
		if (process_heredoc(cmd, &fds) < 0) // Handle heredoc first
		{
			close_fds(&fds);
			return (error(var, "heredoc failed", 1));
		}
		if (cmd->next && pipe(pip) == -1)
		return (error(var, "pipe failed", 1));
		if (handle_builtin(&fds, pip, cmd))
		{
			close_fds(&fds);
			cmd = cmd->next;
			continue ;
		}
		pid = fork();
		if (pid < 0)
			return (error(var, "fork failed", 1));
		if (pid == 0)
			children_process(&fds, pip, cmd, var);
		parent_process(&fds, pip, cmd);
		cmd = cmd->next;
	}
	var->code = wait_children(pid);
	return (1);
}
