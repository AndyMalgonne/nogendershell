/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:00:00 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/31 14:34:47 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open_quotes(const char *rl)
{
	size_t		double_quote;
	size_t		single_quote;
	bool		inside_double_quote;

	double_quote = 0;
	single_quote = 0;
	inside_double_quote = false;
	while (*rl)
	{
		if (*rl == '"')
		{
			double_quote++;
			inside_double_quote = !inside_double_quote;
		}
		else if (*rl == '\'' && !inside_double_quote)
			single_quote++;
		rl++;
	}
	if (double_quote % 2 != 0 || single_quote % 2 != 0)
	{
		ft_putstr_fd("nogendershell: syntax error: open quotes.\n", 2);
		return (0);
	}
	return (1);
}
