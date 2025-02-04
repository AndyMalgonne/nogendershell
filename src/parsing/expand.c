/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:02:37 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/04 14:58:25 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_env_value(char *token_value, t_env *env, size_t i)
{
	size_t	j;
	char	*env_value;
	char	*tmp;
	char	*key;

	j = i + 1;
	while (token_value[j] && !is_space_tab(token_value[j])
		&& token_value[j] != '$' && token_value[j] != '"')
		j++;
	key = ft_substr(token_value, i + 1, j - (i + 1));
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

int	expand(t_token *tokens, t_env *env)
{
	size_t	i;

	while (tokens)
	{
		if (tokens->type == WORD || tokens->type == STRING_DQ)
		{
			i = 0;
			while (tokens->value[i])
			{
				if (tokens->value[i] == '$')
				{
					tokens->value = replace_env_value(tokens->value, env, i);
					if (!tokens->value)
						return (0);
					i = 0;
				}
				else
					i++;
			}
		}
		tokens = tokens->next;
	}
	return (1);
}
