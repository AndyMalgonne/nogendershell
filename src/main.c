/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:02:33 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/11/28 16:57:22 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global = 0;

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main(int ac, char **av, char **envp)
{
	char *input;
	t_token *tokens;

	(void)ac, (void)av, (void)envp;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		input = readline("nogendershell> ");
		if (!input)
			break;
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		print_token_list(tokens);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break;
		}
		free_token_list(&tokens);
		free(input);
	}
	return (0);
}
