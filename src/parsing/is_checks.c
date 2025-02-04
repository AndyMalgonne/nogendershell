/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:00:45 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/31 14:20:32 by abasdere         ###   ########.fr       */
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
