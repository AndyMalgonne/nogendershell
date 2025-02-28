/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:01:30 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/28 12:03:33 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_num_arg(const char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (ft_dprintf(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required", arg), false);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i++]))
		{
			ft_dprintf(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required", arg);
			return (false);
		}
	}
	return (true);
}

int	bi_exit(const t_tree *node, t_var *var, t_fds *fds)
{
	if (node->next != NULL || var->head != node)
		return (set_and_return_code(var, 0));
	ft_putendl_fd("exit", STDERR_FILENO);
	if (node->cmd[1])
	{
		if (!check_num_arg(node->cmd[1]))
			(free_all(var->head, var), close_fds(fds), exit(2));
		if (node->cmd[2])
			return (ft_putendl_fd("minishell: exit: too many arguments",
					STDERR_FILENO), set_and_return_code(var, 1));
		var->code = atoi(node->cmd[1]);
	}
	else
		var->code = 0;
	(free_all(var->head, var), close_fds(fds), exit(var->code));
}
