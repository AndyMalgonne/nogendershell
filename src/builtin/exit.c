/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:01:30 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/26 08:49:27 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_num_arg(const char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i++]))
		{
			ft_putstr_fd("nogendershell: exit: ", STDERR_FILENO);
			ft_putstr_fd((char *)arg, STDERR_FILENO);
			ft_putendl_fd(" numeric argument required", STDERR_FILENO);
			return (false);
		}
	}
	return (true);
}

int	bi_exit(t_tree *node, t_var *var, t_fds *fds)
{
	if (node->next != NULL || var->head != node)
		return (set_and_return_code(var, 0));
	ft_putendl_fd("exit", STDERR_FILENO);
	if (node->cmd[1])
	{
		if (!check_num_arg(node->cmd[1]))
			(free_all(var->head, var), close_fds(fds), exit(2));
		if (node->cmd[2])
			return (ft_putendl_fd("nogendershell: exit: too many arguments",
					STDERR_FILENO), set_and_return_code(var, 1));
		var->code = atoi(node->cmd[1]);
	}
	(free_all(var->head, var), close_fds(fds), exit(var->code));
}
