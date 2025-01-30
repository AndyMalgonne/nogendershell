/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:28:05 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/01/30 13:49:13 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_env(t_env *env)
{
	if (!env)
		return (1);
	while (env->next)
	{
		if (ft_strchr(env->value, '='))
			printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
