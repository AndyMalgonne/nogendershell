/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/10 09:33:15 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_files(t_iofile *io)
{
	int	infd;
	int	outfd;

	infd = 1;
	outfd = 0;
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

int	exec_cmd(t_tree *cmd, const int *pip, t_var *var)
{
	char	*path;
	int		errorr;

	path = get_path_from_env(var->env, &errorr);
	if (errorr == 2)
		return (error(var, "Malloc failed", 1));
	if (io_files(cmd->io) < 0)
		return (error(var, NULL, 1));
	if (cmd->next)
	{
		dup2(pip[1], STDOUT_FILENO);
		close(pip[0]);
		close(pip[1]);
	}
	execve(cmd->cmd[0], cmd->cmd, NULL);
	perror("execve failed");
	return (0);
}

int	minishell_exec(t_tree *cmd, t_var *var)
{
	int		pip[2];
	pid_t	pid;

	while (cmd)
	{
		if (cmd->next && pipe(pip) == -1)
			return (error(var, "pipe failed", 1));
		pid = fork();
		if (pid < 0)
			return (error(var, "fork failed", 1));
		if (pid == 0)
		{
			if (cmd->next)
				close(pip[0]);
			exec_cmd(cmd, pip, var);
		}
		if (cmd->next)
			(close(pip[1]), close(pip[0]));
		cmd = cmd->next;
	}
	return (1);
}
