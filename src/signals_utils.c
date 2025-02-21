/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:41:54 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/21 18:22:31 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_sigint(int sig)
{
	g_exit_flag = sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_child_sigint(int sig)
{
	g_exit_flag = sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	handle_child_sigquit(int sig)
{
	g_exit_flag = sig;
	ft_putstr_fd("Quit\n", STDOUT_FILENO);
}
