/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:57:00 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/26 14:46:09 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	invalid_identifier(const char *id)
{
	ft_dprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n", id);
	return (false);
}

static bool	check_args(const char **args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '=' || ft_isdigit(args[i][0])
			|| (args[i][0] == '_' && args[i][1] == '='))
			return (invalid_identifier(args[i]));
		j = 0;
		while (args[i][j] && args[i][j] != '=')
		{
			if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
				return (invalid_identifier(args[i]));
			++j;
		}
		if (args[i][j] != '=')
			return (invalid_identifier(args[i]));
		++i;
	}
	return (true);
}

static int	add_new_node(char *key, char *value, t_var *var)
{
	t_env	*head;
	t_env	*new;

	head = var->env;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (free(key), free(value), 0);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!head)
		var->env = new;
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
	}
	return (1);
}

int	using_export(const char *id, t_var *var)
{
	char	*key;
	char	*value;
	t_env	*node;

	if (!split_env(id, &key, &value))
		return (0);
	node = get_node_from_key(var->env, key);
	if (!node)
		return (add_new_node(key, value, var));
	free(key);
	free(node->value);
	node->value = value;
	return (1);
}

int	bi_export(const t_tree *node, t_var *var)
{
	size_t	i;

	i = 1;
	if (!node || !node->cmd[1])
		return (ft_putendl_fd("Usage: export name[=word]...",
				STDERR_FILENO),
			set_and_return_code(var, 1));
	if (!check_args((const char **)node->cmd + 1))
		return (set_and_return_code(var, 1));
	if (var->head != node || node->next != NULL)
		return (set_and_return_code(var, 0));
	while (node->cmd[i])
		if (!using_export(node->cmd[i++], var))
			return (ft_putendl_fd(ERR_MALLOC, 2),

				set_and_return_code(var, 1));
	return (set_and_return_code(var, 0));
}
