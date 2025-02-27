/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:58:20 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/27 20:07:37 by amalgonn         ###   ########.fr       */
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

char	*check_file_in_path(char **path, const char *cmd, t_var *var)
{
	int		i;
	char	*file_path;
	char	*full_cmd;

	i = 0;
	while (path && path[i])
	{
		full_cmd = ft_strjoin("/", cmd);
		if (!full_cmd)
			return (NULL);
		file_path = ft_strjoin(path[i], full_cmd);
		free(full_cmd);
		if (!file_path)
			return (NULL);
		if (access(file_path, F_OK) == 0)
		{
			if (access(file_path, X_OK) == 0)
				return (file_path);
			else
				return (ft_dprintf(2, "%s: Permission denied\n", cmd),
					set_and_return_code(var, 126), free(file_path), NULL);
		}
		(free(file_path), i++);
	}
	return (NULL);
}

static int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

static char	*check_cmd_path(char *cmd, t_var *var)
{
	if (is_directory(cmd))
	{
		ft_dprintf(2, "%s: Is a directory\n", cmd);
		return (set_and_return_code(var, 126), free(cmd), NULL);
	}
	if (access(cmd, F_OK) != 0)
	{
		ft_dprintf(2, "%s: No such file or directory\n", cmd);
		return (set_and_return_code(var, 127), free(cmd), NULL);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_dprintf(2, "%s: Permission denied\n", cmd);
		return (set_and_return_code(var, 126), free(cmd), NULL);
	}
	return (cmd);
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
		return (check_cmd_path(cmd, var));
	if (ft_strncmp(cmd, "", 1) == 0)
		return (ft_dprintf(2, "%s: command not found\n", cmd), free(cmd), NULL);
	paths = get_path_from_env(var->env, &errorr);
	if (errorr == 2)
		return (error(var, "Malloc failed", 1), NULL);
	file_path = check_file_in_path(paths, cmd, var);
	ft_fsplit(paths);
	if (file_path)
		return (free(cmd), file_path);
	if (var->code == 126)
		return (free(cmd), NULL);
	set_and_return_code(var, 127);
	ft_dprintf(2, "%s: command not found\n", cmd);
	return (free(cmd), NULL);
}
