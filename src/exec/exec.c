/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:38:56 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/11/05 10:26:09 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if(!cmd)
		return (false);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd) \
	|| !ft_strcmp("pwd", cmd) || !ft_strcmp("export", cmd) \
	|| !ft_strcmp("unset", cmd) || !ft_strcmp("env", cmd) \
	|| !ft_strcmp("exit", cmd))
		return (true);
	return (false);
}

int		exec_builtin(char **args)
{
	if (!ft_strcmp("echo", args[0]))
		return (ft_echo(args));
	if (!ft_strcmp("cd", args[0]))
		return (ft_cd(args));
	if (!ft_strcmp("pwd", args[0]))
		return (ft_pwd());
	if (!ft_strcmp("export", args[0]))
		return (ft_export(args));
	if (!ft_strcmp("unset", args[0]))
		return (ft_unset(args));
	if (!ft_strcmp("env", args[0]))
		return (ft_env());
	if (!ft_strcmp("exit", args[0]))
		return (ft_exit(args));
	return (0);
}
