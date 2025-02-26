/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:28:05 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/26 09:59:46 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_env(t_var *var, const t_tree *node)
{
	if (!var || !node)
		return (1);
	if (node->cmd[1])
		return (ft_putendl_fd("nogendershell: env: too many arguments",
				STDERR_FILENO), set_and_return_code(var, 1));
	return (print_env(var->env), set_and_return_code(var, 0));
}
