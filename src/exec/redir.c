/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:18:37 by amalgonn          #+#    #+#             */
/*   Updated: 2025/02/25 21:08:01 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_fds *fds)
{
	mclose(&(fds->prev_fd));
	mclose(&(fds->infd));
	mclose(&(fds->outfd));
	mclose(&(fds->heredocfd));
}

int	handle_fd_error(const t_iofile *io, t_fds *fds, t_var *var)
{
	if (fds->infd < 0 || fds->outfd < 0)
	{
		error(var, io->value, 1);
		close_fds(fds);
		return (-1);
	}
	return (0);
}

int	io_files(t_iofile *io, t_fds *fds, t_var *var)
{
	while (io)
	{
		if (io->type == INFILE)
		{
			if (fds->infd > 0)
				mclose(&(fds->infd));
			fds->infd = open(io->value, O_RDONLY);
		}
		else if (io->type == OUTFILE_APPEND)
		{
			if (fds->outfd > 1)
				mclose(&(fds->outfd));
			fds->outfd = open(io->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (io->type == OUTFILE_TRUNC)
		{
			if (fds->outfd > 1)
				mclose(&(fds->outfd));
			fds->outfd = open(io->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (handle_fd_error(io, fds, var) < 0)
			return (-1);
		io = io->next;
	}
	return (0);
}

void	handle_input_redirection(t_fds *fds, t_var *var)
{
	if (fds->heredocfd > 0)
	{
		if (dup2(fds->heredocfd, STDIN_FILENO) == -1)
			(close_fds(fds), free_all(var->head, var), exit(1));
		mclose(&(fds->heredocfd));
	}
	if (fds->infd > 0)
	{
		if (dup2(fds->infd, STDIN_FILENO) == -1)
			(close_fds(fds), free_all(var->head, var), exit(1));
		mclose(&(fds->infd));
	}
}

void	redir(t_fds *fds, int pip[2], const t_tree *cmd, t_var *var)
{
	if (fds->prev_fd != -1)
	{
		if (dup2(fds->prev_fd, STDIN_FILENO) == -1)
			(close_fds(fds), free_all(var->head, var), exit(1));
		mclose(&(fds->prev_fd));
	}
	handle_input_redirection(fds, var);
	if (cmd->next)
	{
		if (dup2(pip[1], STDOUT_FILENO) == -1)
			(close_fds(fds), free_all(var->head, var), exit(1));
		mclose(&pip[0]);
		mclose(&pip[1]);
	}
	if (fds->outfd > 1)
	{
		if (dup2(fds->outfd, STDOUT_FILENO) == -1)
			(close_fds(fds), free_all(var->head, var), exit(1));
		mclose(&(fds->outfd));
	}
}
