/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:00:00 by gmoulin           #+#    #+#             */
/*   Updated: 2024/10/31 18:31:51 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open_quotes(const char *rl)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (rl[i])
	{
		if (is_dquote(rl[i]))
			double_quote++;
		if (is_squote(rl[i]))
			single_quote++;
		i++;
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
	int	i;
	int	open_bracket;
	int	close_bracket;

	i = 0;
	open_bracket = 0;
	close_bracket = 0;
	while (rl[i])
	{
		if (is_obracket(rl[i]))
			open_bracket++;
		if (is_cbracket(rl[i]))
			close_bracket++;
		i++;
	}
	if (open_bracket != close_bracket)
	{
		ft_printf("nogendershell: syntax error: open brackets.\n");
		return (1);
	}
	return (0);
}
