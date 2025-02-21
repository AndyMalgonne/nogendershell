/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/21 12:28:19 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_tree *cmd, t_var *var)
{
	char	**env_array;
	char	*full_cmd;

	env_array = linked_list_to_array(var->env);
	if (!env_array)
		(perror("Malloc failed"), free_all(cmd, var), exit(1));
	full_cmd = find_file(cmd->cmd[0], var);
	if (!full_cmd)
		(ft_fsplit(env_array), free_all(cmd, var), exit(127));
	if (execve(full_cmd, cmd->cmd, env_array) == -1)
		(perror("execve failed"), free(full_cmd), ft_fsplit(env_array),
			free_all(cmd, var), exit(1));
	exit(0);
}

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

void	children_process(t_fds *fds, int pip[2], t_tree *cmd, t_var *var)
{
	if (io_files(cmd->io, fds) < 0)
		(free_all(cmd, var), exit(1));
	redir(fds, pip, cmd, var);
	exec_cmd(cmd, var);
}

void	init_fds_and_pid(t_fds *fds, pid_t *pid)
{
	fds->prev_fd = -1;
	fds->infd = 0;
	fds->outfd = 1;
	*pid = 0;
}

int	minishell_exec(t_tree *cmd, t_var *var)
{
	int		pip[2];
	t_fds	fds;
	pid_t	pid;

	init_fds_and_pid(&fds, &pid);
	while (cmd)
	{
		if (pipe(pip) == -1)
			return (error(var, "pipe failed", 1));
		pid = fork();
		if (pid < 0)
			return (error(var, "fork failed", 1));
		if (pid == 0)
			children_process(&fds, pip, cmd, var);
		if (fds.prev_fd != -1)
			mclose(&(fds.prev_fd));
		if (cmd->next)
			(mclose(&pip[1]), fds.prev_fd = pip[0]);
		else
			(mclose(&pip[0]), mclose(&pip[1]));
		cmd = cmd->next;
	}
	wait_children(pid);
	return (1);
}
