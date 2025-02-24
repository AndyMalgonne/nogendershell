/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:18:37 by amalgonn          #+#    #+#             */
/*   Updated: 2025/02/24 20:27:04 by amalgonn         ###   ########.fr       */
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

int	handle_fd_error(const t_iofile *io, t_fds *fds)
{
	if (fds->infd < 0 || fds->outfd < 0)
	{
		perror(io->value);
		mclose(&(fds->infd));
		mclose(&(fds->outfd));
		return (-1);
	}
	return (0);
}

int	io_files(t_iofile *io, t_fds *fds)
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
		if (handle_fd_error(io, fds) < 0)
			return (-1);
		io = io->next;
	}
	return (0);
}

void	redir(t_fds *fds, int pip[2], const t_tree *cmd, t_var *var)
{
	if (fds->prev_fd != -1)
	{
		if (dup2(fds->prev_fd, STDIN_FILENO) == -1)
			(close_fds(fds), free_all(var->head, var), exit(1));
		mclose(&(fds->prev_fd));
	}
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
