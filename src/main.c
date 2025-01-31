/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:02:33 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/01/31 14:25:05 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global = 0;

int	main(int ac, char **av __attribute__((unused)), char **envp)
{
	t_env *env			__attribute__((cleanup(free_env)));
	char *user_input	__attribute__((cleanup(cleanup_user_input)));
	t_tree *tree		__attribute__((cleanup(free_to_null)));

	env = NULL;
	user_input = NULL;
	if (ac != 1)
		return (ft_putstr_fd("Usage: ./minishell\n", 2), 1);
	if (isatty(0) != 1)
		return (ft_putstr_fd("U mad bro?\n", 2), 1);
	if (!create_env(&env, envp))
		return (1);
	while (get_input(&user_input))
	{
		if (!parse_input(user_input, &tree, env))
			return (1);
	}
	return (0);
}
