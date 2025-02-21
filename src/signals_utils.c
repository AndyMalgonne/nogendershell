/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:41:54 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/21 16:46:51 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_parent_sigint(int sig)
{
	g_exit_flag = sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_child_sigint(int sig)
{
	g_exit_flag = sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	handle_child_sigquit(int sig)
{
	g_exit_flag = sig;
	ft_putstr_fd("Quit\n", STDOUT_FILENO);
}

int	set_parent_signals(void)
{
	return (replace_sigaction(SIGINT, &handle_parent_sigint)
		&& register_sigaction(SIGQUIT, NULL, SIG_IGN));
}

int	set_child_signals(void)
{
	return (replace_sigaction(SIGINT, &handle_child_sigint)
		&& replace_sigaction(SIGQUIT, &handle_child_sigquit));
}
