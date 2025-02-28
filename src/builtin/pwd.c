/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:30:59 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/28 11:22:09 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(const t_tree *node, t_var *var)
{
	char	cwd[PATH_MAX];

	if (!var || !node)
		return (1);
	if (getcwd(cwd, PATH_MAX))
		return (ft_putendl_fd(cwd, 1), (set_and_return_code(var, 0)));
	else
		return (perror("getcwd"), set_and_return_code(var, 1));
}
