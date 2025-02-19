/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/19 15:02:42 by abasdere         ###   ########.fr       */
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
		(dup2(infd, STDIN_FILENO), mclose(&infd));
	if (outfd != 1)
		(dup2(outfd, STDOUT_FILENO), mclose(&outfd));
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
	execve(full_cmd, cmd->cmd, env_array);
	(perror("execve failed"),
		free(full_cmd), ft_fsplit(env_array), free_all(cmd, var));
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
			exec_cmd(cmd, var);
		else
			if (cmd->next)
				(mclose(&pip[1]), mclose(&pip[0]));
		cmd = cmd->next;
	}
	wait_children(pid);
	return (1);
}
