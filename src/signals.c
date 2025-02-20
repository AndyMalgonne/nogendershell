/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:24:10 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/21 00:09:22 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_flag = 0;

void	handle_sigint(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	g_exit_flag = SIGINT;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	g_exit_flag = SIGQUIT;
}

void	handle_eof(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	g_exit_flag = EOF;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_flags = SA_SIGINFO;
	sa_int.sa_sigaction = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_flags = SA_SIGINFO;
	sa_quit.sa_sigaction = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
