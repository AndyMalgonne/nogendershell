/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:28:05 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/25 18:48:00 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_env(t_var *env, const char *key)
{
	char	*value;

	if (!env)
		return (1);
	if (key)
	{
		value = get_env_value(env->env, key);
		if (value)
			printf("%s=%s\n", key, value);
		else
			printf("env: '%s': No such file or directory\n", key);
	}
	else
		print_env(env->env);
	return (0);
}
