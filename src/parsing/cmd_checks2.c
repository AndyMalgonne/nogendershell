/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checks2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:01:04 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/06 16:54:57 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_bi_env(const char *rl)
{
	if (ft_strncmp(rl, "env", 3) == 0 && (is_space_tab(rl[3]) || !rl[3]))
		return (1);
	return (0);
}

int	is_bi_exit(const char *rl)
{
	if (ft_strncmp(rl, "exit", 4) == 0 && (is_space_tab(rl[4]) || !rl[4]))
		return (1);
	return (0);
}
