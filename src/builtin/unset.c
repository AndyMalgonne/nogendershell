/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:42:18 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/01/30 13:46:40 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static bool	syntax(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!ft_isalpha(str[i]) && str[i] != '_')
// 		return (false);
// 	i++;
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '_')
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

// static int	already_exist(const char *str, t_env *env)
// {
// 	t_env	*tmp;
// 	int		i;
// 	int		j;

// 	if (!env)
// 		return (-1);
// 	i = 0;
// 	while (str[i])
// 		i++;
// 	j = 0;
// 	tmp = env;
// 	if (!strncmp(str, tmp->str, i))
// 		return (0);
// 	tmp = tmp->next;
// 	j++;
// 	while (tmp != env)
// 	{
// 		if (!strncmp(str, tmp->str, i))
// 			return (j);
// 		tmp = tmp->next;
// 		j++;
// 	}
// 	return (-1);
// }

// static void	check_env(const t_env *tmp, t_env **env)
// {
// 	if (tmp == *env)
// 		*env = (*env)->next;
// 	if (tmp->next == tmp)
// 		*env = NULL;
// }

// static bool	unset(char *str, t_env **env)
// {
// 	t_env	*tmp;
// 	int		i;
// 	int		exist;

// 	i = 0;
// 	if (!str || !(*str))
// 		return (false);
// 	if (!syntax(str))
// 	{
// 		ft_dprintf(2, "minishell: unset: `%s': not a valid identifier\n", str);
// 		return (true);
// 	}
// 	exist = already_exist(str, *env);
// 	if (exist == -1)
// 		return (false);
// 	tmp = *env;
// 	if (!tmp)
// 		return (false);
// 	while (i++ < exist)
// 		tmp = tmp->next;
// 	tmp->prev->next = tmp->next;
// 	tmp->next->prev = tmp->prev;
// 	(free(tmp->str), check_env(tmp, env), free(tmp), tmp = NULL);
// 	return (false);
// }

// int	bi_unset(char **str, t_env **env)
// {
// 	int	exit_code;
// 	int	i;

// 	exit_code = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (unset(str[i], env))
// 			exit_code = 1;
// 		i++;
// 	}
// 	return (exit_code);
// }
