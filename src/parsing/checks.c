/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:00:00 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/30 15:26:11 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	check_open_quotes(const char *rl)
{
	int		double_quote;
	int		single_quote;
	bool	inside_double_quote;

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
		printf("nogendershell: syntax error: open quotes.\n");
		return (1);
	}
	return (0);
}
