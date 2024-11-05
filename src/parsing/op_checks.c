/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:20:13 by gmoulin           #+#    #+#             */
/*   Updated: 2024/10/31 17:27:37 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_rdin(char c)
{
	return (c == '>');
}

int	is_rdout(char c)
{
	return (c == '<');
}

int	is_pipe(char c)
{
	return (c == '|');
}

int	is_scln(char c)
{
	return (c == ';');
}

int	is_and(char c)
{
	return (c == '&');
}
