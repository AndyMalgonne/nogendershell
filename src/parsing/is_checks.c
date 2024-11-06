/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:00:45 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/06 15:47:58 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	return (is_rdin(c) || is_rdout(c) || is_pipe(c) || is_scln(c) || is_and(c));
}

int	is_space_tab(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_cmd(char *rl)
{
	return (is_builtin1(rl) || is_builtin2(rl) || is_builtin3(rl));
}
