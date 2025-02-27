/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:26:44 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/27 20:03:23 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_up_var(t_var *var)
{
	if (!var)
		return ;
	var->code = 0;
	var->env = NULL;
	var->head = NULL;
}

void	free_var(t_var *var)
{
	if (!var)
		return ;
	if (var->env)
		free_env(&var->env);
}

int	set_and_return_code(t_var *var, int code)
{
	if (!var)
		return (1);
	var->code = code;
	return (var->code);
}
