/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:15:50 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/26 20:21:21 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_exit_status(char *value, int exst, size_t i)
{
	char	*status_str;
	char	*tmp;
	char	*result;

	status_str = ft_itoa(exst);
	if (!status_str)
		return (NULL);
	tmp = ft_strndup(value, i);
	if (!tmp)
		return (free(status_str), NULL);
	result = ft_strjoin(tmp, status_str);
	(free(tmp), free(status_str));
	if (!result)
		return (NULL);
	tmp = ft_strjoin(result, &value[i + 2]);
	return (free(result), tmp);
}

static char	*replace_env_value(char *value, t_env *env, size_t i)
{
	size_t		j;
	const char	*env_value;
	char		*tmp;
	char		*key;

	j = i + 1;
	while (value[j] && !is_space_tab(value[j]) && value[j] != '$' \
	&& value[j] != '"' && value[j] != '\n' && value[j] != '\'')
		j++;
	key = ft_substr(value, i + 1, j - (i + 1));
	if (!key)
		return (NULL);
	env_value = get_env_value(env, key);
	(free(key), tmp = ft_strndup(value, i));
	if (!tmp)
		return (NULL);
	if (!env_value)
		key = ft_strdup(tmp);
	else
		key = ft_strjoin(tmp, env_value);
	if (!key)
		return (free(tmp), NULL);
	(free(tmp), tmp = ft_strjoin(key, &value[j]));
	return (free(key), tmp);
}

int	expand_heredoc_value(char **value, t_var *var)
{
	size_t	i;
	char	*new_value;

	i = 0;
	while ((*value)[i])
	{
		if ((*value)[i] == '$')
		{
			if ((*value)[i + 1] == '?')
				new_value = replace_exit_status(*value, var->code, i);
			else
				new_value = replace_env_value(*value, var->env, i);
			if (!new_value)
				return (0);
			free(*value);
			*value = new_value;
			i = 0;
		}
		else
			i++;
	}
	return (1);
}
