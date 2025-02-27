/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:02:37 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/27 17:29:29 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_exit_status(char *token_value, int exst, size_t i)
{
	char	*status_str;
	char	*tmp;
	char	*result;

	status_str = ft_itoa(exst);
	if (!status_str)
		return (NULL);
	tmp = ft_strndup(token_value, i);
	if (!tmp)
		return (free(status_str), NULL);
	result = ft_strjoin(tmp, status_str);
	(free(tmp), free(status_str));
	if (!result)
		return (NULL);
	tmp = ft_strjoin(result, &token_value[i + 2]);
	return (free(result), free(token_value), tmp);
}

static char	*get_env_key(const char *token_value, size_t i, size_t *j)
{
	*j = i + 1;
	while (token_value[*j] && !is_space_tab(token_value[*j])
		&& !is_dollar_end_condition(token_value[*j]))
		(*j)++;
	return (ft_substr(token_value, i + 1, *j - (i + 1)));
}

static char	*replace_env_value(char *token_value, t_env *env, size_t i)
{
	size_t		j;
	const char	*env_value;
	char		*tmp;
	char		*key;

	if (token_value[i + 1] == '\0' || is_space_tab(token_value[i + 1]) \
	|| token_value[i + 1] == '$' || token_value[i + 1] == '"')
		return (ft_strdup(token_value));
	key = get_env_key(token_value, i, &j);
	if (!key)
		return (NULL);
	env_value = get_env_value(env, key);
	(free(key), tmp = ft_strndup(token_value, i));
	if (!tmp)
		return (NULL);
	if (!env_value)
		key = ft_strdup(tmp);
	else
		key = ft_strjoin(tmp, env_value);
	if (!key)
		return (free(tmp), NULL);
	(free(tmp), tmp = ft_strjoin(key, &token_value[j]));
	return (free(key), free(token_value), tmp);
}

static int	expand_token_value(t_token *token, const t_var *var)
{
	size_t	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			if (token->value[i + 1] == '?')
				token->value = replace_exit_status(token->value, var->code, i);
			else
				token->value = replace_env_value(token->value, var->env, i);
			if (!token->value)
				return (0);
			if (token->value[i] == '$')
				i++;
			else
				i = 0;
		}
		else
			i++;
	}
	return (1);
}

int	expand(t_token *tokens, const t_var *var)
{
	while (tokens)
	{
		if ((tokens->type == WORD || tokens->type == STRING_DQ)
			&& !expand_token_value(tokens, var))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
