/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:45:07 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/05 15:56:40 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_echo(char *rl)
{
	if (ft_strncmp(rl, "echo", 4) == 0 && (rl[4] == '\0' || rl[4] == ' '))
		return (1);
	return (0);
}

int	is_cd(char *rl)
{
	if (ft_strncmp(rl, "cd", 2) == 0 && (rl[2] == '\0' || rl[2] == ' '))
		return (1);
	return (0);
}

int	is_pwd(char *rl)
{
	if (ft_strncmp(rl, "pwd", 3) == 0 && (rl[3] == '\0' || rl[3] == ' '))
		return (1);
	return (0);
}

int	is_export(char *rl)
{
	if (ft_strncmp(rl, "export", 6) == 0 && (rl[6] == '\0' || rl[6] == ' '))
		return (1);
	return (0);
}

int	is_unset(char *rl)
{
	if (ft_strncmp(rl, "unset", 5) == 0 && (rl[5] == '\0' || rl[5] == ' '))
		return (1);
	return (0);
}

int	is_env(char *rl)
{
	if (ft_strncmp(rl, "env", 3) == 0 && (rl[3] == '\0' || rl[3] == ' '))
		return (1);
	return (0);
}

int	is_exit(char *rl)
{
	if (ft_strncmp(rl, "exit", 4) == 0 && (rl[4] == '\0' || rl[4] == ' '))
		return (1);
	return (0);
}

int	is_cmd(char *rl)
{
	return (is_echo(rl) || is_cd(rl) || is_pwd(rl) || is_export(rl) || is_unset(rl) || is_env(rl) || is_exit(rl));
}
