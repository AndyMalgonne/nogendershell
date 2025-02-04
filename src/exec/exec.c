/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/04 10:08:27 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int io_files(t_iofile *io)
{
	int infd;
	int outfd;

	infd = 1;
	outfd = 0;
	while (io)
	{
		if (io->type == INFILE)
			infd = open(io->value, O_RDONLY);
		if (io->type == OUTFILE_APPEND)
			outfd = open(io->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (io->type == OUTFILE_TRUNC)
			outfd = open(io->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (infd < 0 || outfd < 0)
				return(perror(io->value), -1);
		io = io->next;
	}
	(dup2(infd, STDIN_FILENO), close(infd));
	(dup2(outfd, STDOUT_FILENO), close(outfd));
	return (0);
}

void exec_cmd(t_tree *cmd, int *pip, t_var *env)
{
    char *path;

    (void)env;
    path = "/bin/ls";
    cmd->cmd[0] = path;

    if (io_files(cmd->io) < 0)
		return ;
    if (cmd->next)
    {
        dup2(pip[1], STDOUT_FILENO);
        close(pip[0]);
        close(pip[1]);
    }
    execve(cmd->cmd[0], cmd->cmd, NULL);
    perror("execve failed");
    return;
}

void minishell_exec(t_tree *cmd, t_var *env)
{
    int pip[2];
    pid_t pid;

    while (cmd)
    {
        if (cmd->next)
            if (pipe(pip) == -1)
			return(perror("pipe failed"));
        pid = fork();
        if (pid < 0)
			return(perror("fork failed"));
        if (pid == 0)
        {
            if (cmd->next)
                close(pip[0]);
            exec_cmd(cmd, pip, env);
        }
        close(pip[1]);
        close(pip[0]);
        cmd = cmd->next;
    }
}
