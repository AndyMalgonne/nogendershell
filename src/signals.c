/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:24:10 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/21 16:59:43 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_flag = 0;

int	set_heredoc_signals(void)
{
	return (replace_sigaction(SIGINT, &handle_child_sigint)
		&& register_sigaction(SIGQUIT, NULL, SIG_IGN));
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

int	replace_sigaction(int signal, void (*handler)(int))
{
	return (register_sigaction(signal, NULL, SIG_IGN)
		&& register_sigaction(signal, NULL, handler));
}
