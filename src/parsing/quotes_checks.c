/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:32:17 by gmoulin           #+#    #+#             */
/*   Updated: 2024/10/31 17:57:33 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(char c)
{
	return (is_squote(c) || is_dquote(c));
}

int	is_squote(char c)
{
	return (c == '\'');
}

int	is_dquote(char c)
{
	return (c == '\"');
}
