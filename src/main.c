/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:02:33 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/01/27 21:26:40 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global = 0;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **envp) //ADD PRINT_TOKEN AFTER TOKENIZE DEBUG
{
	char	*input;
	t_token	*tokens;

	(void)ac, (void)av, (void)envp;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("nogendershell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		if (tokens && tokens->type == BI_EXIT)
			return (free(input), free_token_list(&tokens), 0);
		handle_token_error(&tokens);
		free_token_list(&tokens);
		free(input);
	}
	return (0);
}

bool	is_bi_token(const t_token *token)
{
	if (token->type == BI_ECHO || token->type == BI_CD || token->type == BI_PWD
		|| token->type == BI_EXPORT || token->type == BI_UNSET
		|| token->type == BI_ENV || token->type == BI_EXIT)
		return (true);
	return (false);
}
