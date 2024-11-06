/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:32:17 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/06 15:29:12 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(char c)
{
	return (is_s_quote(c) || is_d_quote(c));
}

int	is_s_quote(char c)
{
	return (c == '\'');
}

int	is_d_quote(char c)
{
	return (c == '\"');
}
