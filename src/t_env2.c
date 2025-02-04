/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:09:53 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/04 13:37:14 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**get_path_from_env(t_env *env, int *error)
{
	const char	*path_value;
	char		**paths;

	path_value = get_env_value(env, "PATH");
	if (!path_value)
	{
		*error = 0;
		return (NULL);
	}
	paths = ft_split(path_value, ':');
	if (!paths)
	{
		*error = 1;
		return (NULL);
	}
	return (paths);
}
