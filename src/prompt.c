/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:54:18 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/27 20:02:57 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input(char **user_input)
{
	const char *raw_input	__attribute__((cleanup(free_to_null)));

	if (!user_input)
		return (0);
	free_to_null(user_input);
	raw_input = readline(PROMPT);
	if (raw_input == NULL)
		return (0);
	*user_input = ft_strtrim(raw_input, SPACES);
	if (*user_input == NULL)
		return (0);
	if (ft_strncmp(raw_input, "", 1) != 0)
		add_history(raw_input);
	return (1);
}

void	cleanup_user_input(char **user_input)
{
	if (user_input && *user_input)
		free_to_null(user_input);
	rl_clear_history();
}
