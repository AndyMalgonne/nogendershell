/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/20 21:10:32 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_files(t_iofile *io, int *infd, int *outfd)
{
	while (io)
	{
		if (io->type == INFILE)
		{
			if (*infd > 0)
				mclose(infd);
			*infd = open(io->value, O_RDONLY);
		}
		else if (io->type == OUTFILE_APPEND)
		{
			if (*outfd > 1)
				mclose(outfd);
			*outfd = open(io->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (io->type == OUTFILE_TRUNC)
		{
			if (*outfd > 1)
				mclose(outfd);
			*outfd = open(io->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (*infd < 0 || *outfd < 0)
			return (perror(io->value), mclose(infd), mclose(outfd), -1);
		io = io->next;
	}
	return (0);
}

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

void	redir(int prev_fd, int pip[2], int in, int out, t_tree *cmd, t_var *var)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			(mclose(&prev_fd), exit(1));
		mclose(&prev_fd);
	}
	if (in > 0)
	{
		if (dup2(in, STDIN_FILENO) == -1)
			(mclose(&in), free_all(cmd, var), exit(1));
		mclose(&in);
	}
	if (cmd->next)
	{
		if (dup2(pip[1], STDOUT_FILENO) == -1)
			(mclose(&pip[1]), exit(1));
	}
	if (out > 1)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
			(mclose(&out), free_all(cmd, var), exit(1));
		mclose(&out);
	}
	mclose(&pip[0]);
	mclose(&pip[1]);
}

void	children_process(int prev_fd, int pip[2], t_tree *cmd, t_var *var)
{
	int		infd;
	int		outfd;

	infd = 0;
	outfd = 1;
	if (io_files(cmd->io, &infd, &outfd) < 0)
		(free_all(cmd, var), exit(1));
	redir(prev_fd, pip, infd, outfd, cmd, var);
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
		if (pipe(pip) == -1)
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
		else
			(mclose(&pip[0]), mclose(&pip[1]));
		cmd = cmd->next;
	}
	wait_children(pid);
	return (1);
}
