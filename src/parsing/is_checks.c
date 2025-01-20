/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:00:45 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/20 23:58:20 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	return (is_rdin(c) || is_rdout(c) || is_pipe(c) || is_scln(c) || is_and(c) \
	|| is_backlash(c));
}

int	is_space_tab(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_cmd(char *rl)
{
	return (is_bi_echo(rl) || is_bi_cd(rl) || is_bi_pwd(rl) \
	|| is_bi_export(rl) || is_bi_unset(rl) || is_bi_env(rl) \
	|| is_bi_exit(rl));
}
