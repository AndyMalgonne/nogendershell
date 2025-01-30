/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:00:45 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/30 16:26:02 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_space_tab(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_quotes(char c)
{
	return (c == '\'' || c == '\"');
}
