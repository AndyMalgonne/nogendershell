/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:24:10 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/21 16:45:09 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_flag = 0;

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
