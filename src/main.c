/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:02:33 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/17 10:29:02 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global = 0;

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
	while (get_input(&user_input))
	{
		if (!parse_input(user_input, &tree, &var))
			break ;
		minishell_exec(tree, &var);
		free_tree(&tree);
	}
	return (var.code);
}
