/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/19 18:49:44 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_files(t_iofile *io)
{
	int	infd;
	int	outfd;

	infd = 0;
	outfd = 1;
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
	if (infd != 0)
		if ((dup2(infd, STDIN_FILENO), mclose(&infd)) == -1)
			return (-1);
	if (outfd != 1)
		if ((dup2(outfd, STDOUT_FILENO), mclose(&outfd)) == -1)
			return (-1);
	return (0);
}

void	exec_cmd(t_tree *cmd, t_var *var)
{
	char	**env_array;
	char	*full_cmd;

	if (io_files(cmd->io) < 0)
		(free_all(cmd, var), exit(1));
	env_array = linked_list_to_array(var->env);
	if (!env_array)
		(perror("Malloc failed"), free_all(cmd, var), exit(1));
	full_cmd = find_file(cmd->cmd[0], var);
	if (!full_cmd)
		(ft_fsplit(env_array), free_all(cmd, var), exit(127));
	if (execve(full_cmd, cmd->cmd, env_array) == -1)
		(perror("execve failed"), free(full_cmd), ft_fsplit(env_array),
			free_all(cmd, var));
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

void	children_process(int prev_fd, int pip[2], t_tree *cmd, t_var *var)
{
	if (prev_fd != -1)
		if ((dup2(prev_fd, STDIN_FILENO), mclose(&prev_fd)) == -1)
			exit(1);
	if (cmd->next)
		if ((dup2(pip[1], STDOUT_FILENO), mclose(&pip[1]), mclose(&pip[0])) == -1)
			exit(1);
	exec_cmd(cmd, var);
}

int	minishell_exec(t_tree *cmd, t_var *var)
{
	int		pip[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	pid = 0;
	while (cmd)
	{
		if (cmd->next && pipe(pip) == -1)
			return (error(var, "pipe failed", 1));
		pid = fork();
		if (pid < 0)
			return (error(var, "fork failed", 1));
		if (pid == 0)
			children_process(prev_fd, pip, cmd, var);
		if (prev_fd != -1)
			mclose(&prev_fd);
		if (cmd->next)
			(mclose(&pip[1]), prev_fd = pip[0]);
		cmd = cmd->next;
	}
	wait_children(pid);
	return (1);
}
