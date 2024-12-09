/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:58:20 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/12/09 11:49:49 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcut(const char *str, const char stop)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != stop)
		i++;
	return (ft_substr(str, 0, i));
}

char	**find_path(char **envp)
{
	int		i;
	char	*tmp;
	char	**path;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		if (path[i][ft_strlen(path[i]) - 1] != '/')
		{
			tmp = ft_strjoin(path[i], "/");
			if (!tmp)
				return (ft_fsplit(path), NULL);
			free(path[i]);
			path[i] = tmp;
		}
	}
	return (path);
}

char	*check_file_in_path(char **path, const char *cmd)
{
	int		i;
	char	*file_path;

	i = 0;
	while (path != NULL)
	{
		i++;
		if (!path[i])
			break ;
		file_path = ft_strjoin(path[i], cmd);
		if (!file_path)
			return (NULL);
		if (access(file_path, F_OK | X_OK) == 0)
			return (file_path);
		free(file_path);
	}
	return (NULL);
}

char	*find_file(char *cmd, char **path)
{
	char	*file_path;

	cmd = ft_strcut(cmd, ' ');
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (cmd);
	if (ft_strncmp(cmd, "", 1) == 0)
		return (ft_dprintf(2, "%s: command not found\n", cmd), free(cmd), NULL);
	file_path = check_file_in_path(path, cmd);
	if (file_path)
		return (free(cmd), file_path);
	ft_dprintf(2, "%s: command not found\n", cmd);
	return (free(cmd), NULL);
}
