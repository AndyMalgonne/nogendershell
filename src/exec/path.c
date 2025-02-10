/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andytropmimi <andytropmimi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:58:20 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/10 14:31:54 by andytropmim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_from_env(t_env *env, int *error)
{
	const char	*path_value;
	char		**paths;

	path_value = get_env_value(env, "PATH");
	if (!path_value)
	{
		*error = 1;
		return (NULL);
	}
	paths = ft_split(path_value, ':');
	if (!paths)
	{
		*error = 2;
		return (NULL);
	}
	*error = 0;
	return (paths);
}

char	*check_file_in_path(char **path, const char *cmd)
{
	int		i;
	char	*file_path;
	char	*full_cmd;

	i = 0;
	while (path && path[++i])
	{
		full_cmd = ft_strjoin("/", cmd);
		if (!full_cmd)
			return (NULL);
		file_path = ft_strjoin(path[i], full_cmd);
		free(full_cmd);
		if (!file_path)
			return (NULL);
		if (access(file_path, F_OK | X_OK) == 0)
			return (file_path);
		free(file_path);
	}
	return (NULL);
}

char	*find_file(char *cmd, t_var *var)
{
	char	*file_path;
	char	**paths;
	int		errorr;

	cmd = ft_strcut(cmd, ' ');
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (cmd);
	if (ft_strncmp(cmd, "", 1) == 0)
		return (ft_dprintf(2, "%s: command not found\n", cmd), free(cmd), NULL);
	paths = get_path_from_env(var->env, &errorr);
	if (errorr == 2)
		return (error(var, "Malloc failed", 1), NULL);
	file_path = check_file_in_path(paths, cmd);
	if (file_path)
		return (free(cmd), file_path);
	ft_dprintf(2, "%s: command not found\n", cmd);
	return (free(cmd), NULL);
}
