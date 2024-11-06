/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_check_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:13:24 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/06 15:47:11 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin1(char *rl)
{
	return (is_bi_echo(rl) || is_bi_cd(rl) || is_bi_pwd(rl));
}

static int	is_builtin2(char *rl)
{
	return (is_bi_export(rl) || is_bi_unset(rl) || is_bi_env(rl));
}

static int	is_builtin3(char *rl)
{
	return (is_bi_exit(rl));
}