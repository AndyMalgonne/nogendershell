/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:43:14 by amalgonn          #+#    #+#             */
/*   Updated: 2025/02/27 20:03:07 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**convert_env_to_array(t_env *env, char **env_array, int *size)
{
	char	*temp;

	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		if (!temp)
			return (ft_fsplit(env_array), NULL);
		env_array[*size] = ft_strjoin(temp, env->value);
		free(temp);
		if (!env_array[*size])
			return (ft_fsplit(env_array), NULL);
		(*size)++;
		env = env->next;
	}
	return (env_array);
}

char	**linked_list_to_array(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**env_array;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_array = ft_calloc(i + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	env_array = convert_env_to_array(env, env_array, &i);
	if (!env_array)
		return (NULL);
	env_array[i] = NULL;
	return (env_array);
}

t_env	*get_node_from_key(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
