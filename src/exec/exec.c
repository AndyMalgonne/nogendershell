/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/17 17:21:49 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_files(t_iofile *io)
{
	int	infd;
	int	outfd;

	infd = 1;
	outfd = 0;
	if (!io)
		return (0);
	while (io)
	{
		if (io->type == INFILE && mclose(&infd))
			infd = open(io->value, O_RDONLY);
		if (io->type == OUTFILE_APPEND && mclose(&outfd))
			outfd = open(io->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (io->type == OUTFILE_TRUNC && mclose(&outfd))
			outfd = open(io->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (infd < 0 || outfd < 0)
			return (perror(io->value), -1);
		io = io->next;
	}
	return (0);
}

int	exec_cmd(t_tree *cmd, t_var *var)
{
	char	**env_array;
	char	*full_cmd;

	if (io_files(cmd->io) < 0)
		return (error(var, NULL, 1));
	env_array = linked_list_to_array(var->env);
	if (!env_array)
		return (ft_fsplit(env_array), error(var, "Malloc failed", 1));
	full_cmd = find_file(cmd->cmd[0], var);
	if (!full_cmd)
		return (error(var, "Command not found", 127));
	if (execve(full_cmd, cmd->cmd, env_array) == -1)
		(perror("execve failed"), free(full_cmd), ft_fsplit(env_array));
	return (0);
}

void	child_process(t_tree *cmd, int *pip, t_var *var, int first_fd)
{
	if (first_fd != -1)
	{
		dup2(first_fd, STDIN_FILENO);
		mclose(&first_fd);
	}
	if (cmd->next)
	{
		if (dup2(pip[1], STDOUT_FILENO) == -1)
			error(var, "dup2 failed", 1);
		mclose(&pip[0]);
		mclose(&pip[1]);
	}
	exec_cmd(cmd, var);
	exit(1);
}

void	parent_process(const t_tree *cmd, int *pip, int *first_fd)
{
	if (*first_fd != -1)
		mclose(first_fd);
	if (cmd->next)
	{
		mclose(&pip[1]);
		*first_fd = pip[0];
	}
	else
		mclose(&pip[0]);
}

int	minishell_exec(t_tree *cmd, t_var *var)
{
	int		pip[2];
	int		first_fd;
	pid_t	pid;

	first_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pip) == -1)
			return (error(var, "pipe failed", 1));
		pid = fork();
		if (pid < 0)
			return (error(var, "fork failed", 1));
		if (pid == 0)
			child_process(cmd, pip, var, first_fd);
		else
			parent_process(cmd, pip, &first_fd);
		waitpid(pid, NULL, 0);
		cmd = cmd->next;
	}
	return (1);
}
