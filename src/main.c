/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:02:33 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/17 19:22:12 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(t_var *var, char **user_input, t_tree **tree)
{
	while (!g_exit_flag)
	{
		if (get_input(user_input) == 0)
		{
			if (g_exit_flag)
				handle_eof();;
			break ;
		}
		if (!parse_input(*user_input, tree, var))
			break ;
		free_tree(tree);
	}
}

int	main(int ac, char **av __attribute__((unused)), char **envp)
{
	t_var var			__attribute__((cleanup(free_var)));
	char *user_input	__attribute__((cleanup(cleanup_user_input)));
	t_tree *tree		__attribute__((cleanup(free_tree)));

	set_up_var(&var);
	user_input = NULL;
	tree = NULL;
	if (ac != 1)
		return (ft_putstr_fd("Usage: ./minishell\n", 2), 1);
	if (isatty(0) != 1)
		return (ft_putstr_fd("U mad bro?\n", 2), 1);
	if (!create_env(&var.env, envp))
		return (1);
	setup_signal_handlers();
	main_loop(&var, &user_input, &tree);
	return (var.code);
}
