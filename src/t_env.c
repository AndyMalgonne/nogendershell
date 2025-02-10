/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:27:14 by abasdere          #+#    #+#             */
/*   Updated: 2025/02/03 09:28:48 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_env(const char *env_str, char **key, char **value)
{
	const char	*equal_sign;
	size_t		index;
	size_t		len;

	equal_sign = ft_strchr(env_str, '=');
	len = ft_strlen(env_str);
	index = len;
	if (equal_sign != NULL)
		index = equal_sign - env_str;
	*key = ft_substr(env_str, 0, index);
	if (*key == NULL)
		return (0);
	if (equal_sign)
	{
		*value = ft_substr(env_str, index + 1, len - (index + 1));
		if (*value == NULL)
			return (free_to_null(key), 0);
	}
	return (1);
}

int	create_env(t_env **env, char **envp)
{
	t_env	**head;
	t_env	*new_node;
	size_t	i;

	i = -1;
	head = env;
	while (envp[++i])
	{
		new_node = ft_calloc(1, sizeof(t_env));
		if (new_node == NULL)
			return (ft_putstr_fd(ERR_MALLOC, 2), 0);
		new_node->key = NULL;
		new_node->value = NULL;
		new_node->next = NULL;
		if (!split_env(envp[i], &new_node->key, &new_node->value))
			return (ft_putstr_fd(ERR_MALLOC, 2), 0);
		*head = new_node;
		head = &new_node->next;
	}
	return (1);
}

void	free_env(t_env **env)
{
	if (!env || !(*env))
		return ;
	if ((*env)->next)
		free_env(&(*env)->next);
	if ((*env)->key)
		free((*env)->key);
	if ((*env)->value)
		free((*env)->value);
	free(*env);
}

void	print_env(const t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

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