/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/19 11:18:46 by amalgonn         ###   ########.fr       */
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
	printf("infd: %d\n", infd);
	printf("outfd: %d\n", outfd);
	if (infd != 0)
		(dup2(infd, STDIN_FILENO), mclose(&infd));
	if (outfd != 1)
		(dup2(outfd, STDOUT_FILENO), mclose(&outfd));
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

int	minishell_exec(t_tree *cmd, t_var *var)
{
	int		pip[2];
	pid_t	pid;

	pid = 0;
	while (cmd)
	{
		if (cmd->next && pipe(pip) == -1)
			return (error(var, "pipe failed", 1));
		pid = fork();
		if (pid < 0)
			return (error(var, "fork failed", 1));
		if (pid == 0)
			return (exec_cmd(cmd, var), 0);
		else
			if (cmd->next)
				(mclose(&pip[1]), mclose(&pip[0]));
		cmd = cmd->next;
	}
	wait_children(pid);
	return (1);
}
