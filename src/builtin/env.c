/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:28:05 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/26 13:32:08 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_env(const t_tree *node, t_var *var)
{
	if (!var || !node)
		return (1);
	if (node->cmd[1])
		return (ft_putendl_fd("nogendershell: env: too many arguments",
				STDERR_FILENO), set_and_return_code(var, 1));
	return (print_env(var->env), set_and_return_code(var, 0));
}
