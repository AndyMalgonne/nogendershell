/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:02:33 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/21 00:09:26 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_exit_status(t_var *var)
{
	if (g_exit_flag == SIGINT)
		set_and_return_code(var, 130);
	else if (g_exit_flag == SIGQUIT)
		set_and_return_code(var, 131);
	else if (g_exit_flag == EOF)
		set_and_return_code(var, 0);
}

void	main_loop(t_var *var, char **user_input, t_tree **tree)
{
	while (get_input(user_input))
	{
		signal_exit_status(var);
		g_exit_flag = 0;
		if (!parse_input(*user_input, tree, var))
			break ;
		if (!minishell_exec(*tree, var))
			break ;
		free_tree(tree);
	}
}

int	main(int ac, char **av __attribute__((unused)), char **envp)
{
	t_var var			__attribute__((cleanup(free_var)));
	char *input			__attribute__((cleanup(cleanup_user_input)));
	t_tree *tree		__attribute__((cleanup(free_tree)));

	set_up_var(&var);
	input = NULL;
	tree = NULL;
	if (ac != 1)
		return (ft_putstr_fd("Usage: ./minishell\n", 2), 1);
	if (isatty(0) != 1)
		return (ft_putstr_fd("U mad bro?\n", 2), 1);
	if (!create_env(&var.env, envp))
		return (1);
	setup_signal_handlers();
	main_loop(&var, &input, &tree);
	return (var.code);
}
