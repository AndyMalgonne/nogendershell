/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:42:18 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/26 11:19:08 by amalgonn         ###   ########.fr       */
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

static bool	unset(char *cmd, t_env **env)
{
	t_env	*tmp;
	t_env	*next;
	int		l;

	if (!cmd || !(*cmd) || !env || !*env)
		return (false);
	if (!syntax(cmd))
		return (ft_dprintf(2, "unset: `%s': not valid\n", cmd), true);
	l = 0;
	while (cmd[l] && cmd[l] != '=')
		l++;
	tmp = *env;
	while (tmp && tmp->next)
	{
		if (!ft_strncmp(cmd, tmp->next->key, l) && tmp->next->key[l] == '\0')
		{
			next = tmp->next;
			tmp->next = tmp->next->next;
			return (free(next->key), free(next->value), free(next), false);
		}
		tmp = tmp->next;
	}
	return (false);
}

int	bi_unset(char **cmd, t_env **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (cmd[i])
	{
		if (unset(cmd[i], env))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
