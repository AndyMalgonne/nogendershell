/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:00:45 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/28 10:22:33 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
