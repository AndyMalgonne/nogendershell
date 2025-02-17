/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/17 09:41:49 by amalgonn         ###   ########.fr       */
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
	(dup2(infd, STDIN_FILENO), close(infd));
	(dup2(outfd, STDOUT_FILENO), close(outfd));
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
		return (error(var, "Malloc failed", 1));
	full_cmd = find_file(cmd->cmd[0], var);
	if (!full_cmd)
		return (error(var, "Command not found", 127));
	execve(full_cmd, cmd->cmd, env_array);
	perror("execve failed");
	free(full_cmd);
	ft_fsplit(env_array);
	return (0);
}

void	child_process(t_tree *cmd, const int *pip, t_var *var)
{
	if (cmd->next)
	{
		dup2(pip[1], STDOUT_FILENO);
		close(pip[0]);
		close(pip[1]);
	}
	exec_cmd(cmd, var);
	exit(1);
}

void	parent_process(pid_t pid, const int *pip, int has_next)
{
	if (has_next)
	{
		close(pip[1]);
		dup2(pip[0], STDIN_FILENO);
		close(pip[0]);
	}
	waitpid(pid, NULL, 0);
}

int	minishell_exec(t_tree *cmd, t_var *var)
{
	int		pip[2];
	pid_t	pid;
	int		has_next;

	while (cmd)
	{
		has_next = cmd->next != NULL;
		if (cmd->next && pipe(pip) == -1)
			return (error(var, "pipe failed", 1));
		pid = fork();
		if (pid < 0)
			return (error(var, "fork failed", 1));
		if (pid == 0)
			child_process(cmd, pip, var);
		else
			parent_process(pid, pip, has_next);
		cmd = cmd->next;
	}
	return (1);
}
