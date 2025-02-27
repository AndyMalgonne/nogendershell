/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:00:00 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/27 13:54:49 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote_status(const char *rl, t_quote_status *status)
{
	if (*rl == '"' && !status->inside_single_quote)
	{
		status->double_quote++;
		status->inside_double_quote = !status->inside_double_quote;
	}
	else if (*rl == '\'' && !status->inside_double_quote)
	{
		status->single_quote++;
		status->inside_single_quote = !status->inside_single_quote;
	}
}

int	check_open_quotes(const char *rl)
{
	t_quote_status	status;

	status.double_quote = 0;
	status.single_quote = 0;
	status.inside_double_quote = false;
	status.inside_single_quote = false;
	while (*rl)
	{
		update_quote_status(rl, &status);
		rl++;
	}
	if (status.double_quote % 2 != 0 || status.single_quote % 2 != 0)
	{
		ft_putstr_fd("nogendershell: syntax error: open quotes.\n", 2);
		return (0);
	}
	return (1);
}
