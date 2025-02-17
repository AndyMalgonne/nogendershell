/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:54:18 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/17 12:32:44 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input(char **user_input)
{
	if (!user_input)
		return (0);
	free_to_null(user_input);
	*user_input = readline(PROMPT);
	if (*user_input == NULL)
		return (0);
	if (ft_strncmp(*user_input, "", 1) != 0)
		add_history(*user_input);
	return (1);
}

void	cleanup_user_input(char **user_input)
{
	if (!user_input || !(*user_input))
		return ;
	free_to_null(user_input);
	rl_clear_history();
}
