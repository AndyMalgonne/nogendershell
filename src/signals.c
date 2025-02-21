/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:24:10 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/21 10:33:08 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_flag = 0;

static void	handle_sigint(int sig)
{
	g_exit_flag = sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	register_sigaction(int sig, struct sigaction *old, void (*handler)(int))
{
	struct sigaction	saction;
	sigset_t			set;

	sigemptyset(&set);
	saction.sa_handler = handler;
	saction.sa_mask = set;
	saction.sa_flags = 0;
	if (sigaction(sig, &saction, old) == -1)
		return (perror("sigaction"), 0);
	return (1);
}

int	setup_main_signal_handlers(void)
{
	return (register_sigaction(SIGINT, NULL, &handle_sigint)
		&& register_sigaction(SIGQUIT, NULL, SIG_IGN));
}
