/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:02:33 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/26 15:08:28 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_signal_code(t_var *var)
{
	if (g_exit_flag == SIGINT)
		var->code = 130;
	g_exit_flag = 0;
}

static void	main_loop(t_var *var, char **user_input, t_tree **tree)
{
	while (set_signals(&handle_parent_sigint, SIG_IGN) && get_input(user_input))
	{
		check_signal_code(var);
		if (!set_signals(&handle_child_sigint, &handle_child_sigquit)
			|| !parse_input(*user_input, tree, var))
			break ;
		(free_to_null(user_input), var->head = *tree);
		if (!minishell_exec(*tree, var))
			break ;
		(free_tree(tree), var->head = NULL);
	}
	check_signal_code(var);
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
	main_loop(&var, &input, &tree);
	return (ft_putstr_fd("exit\n", STDOUT_FILENO), var.code);
}
