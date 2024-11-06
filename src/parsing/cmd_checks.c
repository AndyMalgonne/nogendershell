/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:45:07 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/06 15:45:06 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_bi_echo(char *rl)
{
	if (ft_strncmp(rl, "echo", 4) == 0 && (is_space_tab(rl[4]) || !rl[4]))
		return (1);
	return (0);
}

int	is_bi_cd(char *rl)
{
	if (ft_strncmp(rl, "cd", 2) == 0 && (is_space_tab(rl[2]) || !rl[2]))
		return (1);
	return (0);
}

int	is_bi_pwd(char *rl)
{
	if (ft_strncmp(rl, "pwd", 3) == 0 && (is_space_tab(rl[3]) || !rl[3]))
		return (1);
	return (0);
}

int	is_bi_export(char *rl)
{
	if (ft_strncmp(rl, "export", 6) == 0 && (is_space_tab(rl[6]) || !rl[6]))
		return (1);
	return (0);
}

int	is_bi_unset(char *rl)
{
	if (ft_strncmp(rl, "unset", 5) == 0 && (is_space_tab(rl[5]) || !rl[5]))
		return (1);
	return (0);
}
