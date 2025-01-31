/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:02:33 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/01/31 13:34:35 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "tokens.h"

int	g_global = 0;

int	main(int ac, char **av __attribute__((unused)), char **envp)
{
	t_env *env			__attribute__((cleanup(free_env)));
	char *user_input	__attribute__((cleanup(cleanup_user_input)));

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
	}
	return (0);
}

//int	main(int ac, char **av __attribute__((unused)), char **envp)
//{
//	t_env *env			__attribute__((cleanup(free_env)));
//	char *user_input	__attribute__((cleanup(cleanup_user_input)));
//	 t_token	*tokens;

//	env = NULL;
//	user_input = NULL;
//	 tokens = NULL;
//	if (ac != 1)
//		return (ft_putstr_fd("Usage: ./minishell\n", 2), 1);
//	if (isatty(0) != 1)
//		return (ft_putstr_fd("U mad bro?\n", 2), 1);
//	if (!create_env(&env, envp))
//		return (1);
//	while (get_input(&user_input))
//	{
//		 tokens = tokenize(user_input);
//		 if (tokens && tokens->type == BI_EXIT)
//		 	return (free_token_list(&tokens), 0);
//		 handle_token_error(&tokens);
//		 free_token_list(&tokens);
//	}
//	return (0);
//}
