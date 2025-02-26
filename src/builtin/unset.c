/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:42:18 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/26 12:01:26 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	syntax(const char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static bool	unset(char *cmd, t_var *var)
{
	t_env	*node;
	t_env	*tmp;

	if (!cmd || !var)
		return (false);
	if (!syntax(cmd))
	{
		ft_dprintf(2, "minishell: unset: `%s': not a valid identifier\n", cmd);
		return (true);
	}
	node = get_node_from_key(var->env, cmd);
	if (!node)
		return (false);
	if (node == var->env)
		var->env = node->next;
	else
	{
		tmp = var->env;
		while (tmp && tmp->next != node)
			tmp = tmp->next;
		if (tmp)
			tmp->next = node->next;
	}
	(free(node->key), free(node->value), free(node));
	return (false);
}

int	bi_unset(char **cmd, t_var **var)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (cmd[i])
	{
		if (unset(cmd[i], *var))
			return (set_and_return_code(*var, 1));
		i++;
	}
	return (set_and_return_code(*var, exit_code));
}
