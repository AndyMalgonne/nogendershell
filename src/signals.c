/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:24:10 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/21 18:27:04 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_flag = 0;

static int	register_sigaction(int sig,
	struct sigaction *old, void (*handler)(int))
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

static int	replace_sigaction(int signal, void (*handler)(int))
{
	return (register_sigaction(signal, NULL, SIG_IGN)
		&& register_sigaction(signal, NULL, handler));
}

int set_signals(void (*handler_sigint)(int), void (*handler_sigquit)(int))
{
	int n;

	n = 0;
	n += replace_sigaction(SIGINT, handler_sigint);
	if (handle_child_sigquit == SIG_IGN)
		n += register_sigaction(SIGQUIT, NULL, SIG_IGN);
	else
		n += replace_sigaction(SIGQUIT, handler_sigquit);
	return (n == 2);
}
