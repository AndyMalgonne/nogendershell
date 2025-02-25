/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:24:10 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/25 21:14:49 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"
#include "minishell.h"

int	g_exit_flag = 0;

static int	register_sigaction(int sig,
	struct sigaction *old, void (*handler)(int), t_var *var)
{
	struct sigaction	saction;
	sigset_t			set;

	sigemptyset(&set);
	saction.sa_handler = handler;
	saction.sa_mask = set;
	saction.sa_flags = 0;
	if (sigaction(sig, &saction, old) == -1)
		return (error(var, "sigaction", 1), 0);
	return (1);
}

static int	replace_sigaction(int signal, void (*handler)(int), t_var *var)
{
	return (register_sigaction(signal, NULL, SIG_IGN, var)
		&& register_sigaction(signal, NULL, handler, var));
}

int	set_signals(void (*handler_sigint)(int), void (*handler_sigquit)(int),
	t_var *var)
{
	int	n;

	n = 0;
	n += replace_sigaction(SIGINT, handler_sigint, var);
	if (handle_child_sigquit == SIG_IGN)
		n += register_sigaction(SIGQUIT, NULL, SIG_IGN, var);
	else
		n += replace_sigaction(SIGQUIT, handler_sigquit, var);
	return (n == 2);
}
