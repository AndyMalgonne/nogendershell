/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:28:05 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/11/20 12:41:55 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (0);
	if (ft_strchr(tmp->str, '='))
		printf("%s\n", tmp->str);
	tmp = tmp->next;
	while (tmp != env)
	{
		if (ft_strchr(tmp->str, '='))
			printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	return (0);
}
