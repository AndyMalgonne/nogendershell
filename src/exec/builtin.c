/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:59:16 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/01/30 15:25:41 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_tree *node)
{
	if (ft_strcmp(node->cmd[0], "echo") == 0)
		return (true);
	if (ft_strcmp(node->cmd[0], "cd") == 0)
		return (true);
	if (ft_strcmp(node->cmd[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(node->cmd[0], "export") == 0)
		return (true);
	if (ft_strcmp(node->cmd[0], "unset") == 0)
		return (true);
	if (ft_strcmp(node->cmd[0], "env") == 0)
		return (true);
	if (ft_strcmp(node->cmd[0], "exit") == 0)
		return (true);
	return (false);
}
