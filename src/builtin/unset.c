/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:42:18 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/11/25 10:29:48 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//parsing
static bool	syntax(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	already_exist(char *str, t_env *env)
{
	t_env	*tmp;
	int		i;
	int		j;

	if (!env)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	j = 0;
	tmp = env;
	if (!strncmp(str, tmp->str, i))
		return (0);
	tmp = tmp->next;
	j++;
	while (tmp != env)
	{
		if (!strncmp(str, tmp->str, i))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

static void	check_env(t_env *tmp, t_env **env)
{
	if (tmp == *env)
		*env = (*env)->next;
	if (tmp->next == tmp)
		*env = NULL;
}

static bool	unset(char *str, t_env **env)
{
	t_env	*tmp;
	int		i;
	int		exist;

	i = 0;
	if (!str || !(*str))
		return (false);
	if (!syntax(str))
		return (error("unset: invalid identifier\n"), true);
	exist = already_exist(str, *env);
	if (exist == -1)
		return (false);
	tmp = *env;
	while (i++ < exist)
		tmp = tmp->next;
	if(!tmp)
		return (false);
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	(free(tmp->str), check_env(tmp, env), free(tmp), tmp = NULL);
	return (false);
}

int	bi_unset(char **str, t_env **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (str[i])
	{
		if (unset(str[i], env))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
