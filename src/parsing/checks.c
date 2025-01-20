/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:00:00 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/20 23:02:14 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (is_d_quote(*rl))
		{
			double_quote++;
			inside_double_quote = !inside_double_quote;
		}
		else if (is_s_quote(*rl) && !inside_double_quote)
			single_quote++;
		rl++;
	}
	if (double_quote % 2 != 0 || single_quote % 2 != 0)
	{
		ft_printf("nogendershell: syntax error: open quotes.\n");
		return (1);
	}
	return (0);
}

int	check_open_brackets(const char *rl)
{
	int		bracket_count;
	bool	inside_string;

	bracket_count = 0;
	inside_string = false;
	while (*rl)
	{
		if (is_d_quote(*rl) || is_s_quote(*rl))
			inside_string = !inside_string;
		else if (!inside_string)
		{
			if (is_o_bracket(*rl))
				bracket_count++;
			else if (is_c_bracket(*rl))
				bracket_count--;
		}
		rl++;
	}
	if (bracket_count != 0)
	{
		ft_printf("nogendershell: syntax error: unmatched brackets.\n");
		return (1);
	}
	return (0);
}
