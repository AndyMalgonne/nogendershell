/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:02:32 by amalgonn          #+#    #+#             */
/*   Updated: 2025/02/26 16:06:07 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	echo_strlen(char **cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

static void	update_oldpwd(t_var *var)
{
	t_env	*tmp;
	char	*oldpwd;

	oldpwd = NULL;
	tmp = var->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", 3) == 0)
		{
			oldpwd = ft_strjoin("OLDPWD=", tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (!oldpwd)
		using_export("OLDPWD", var);
	else
		(using_export(oldpwd, var), free(oldpwd));
}

static void	update_pwd(const char *cmd, t_var *var)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_oldpwd(var);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		(perror(cmd), set_and_return_code(var, 1));
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
	{
		(perror(cmd), set_and_return_code(var, 1));
		return ;
	}
	using_export(pwd, var);
	free(pwd);
}

int	bi_cd(char **cmd, t_var *var)
{
	int	result;

	if (!cmd || !var || !var->env)
		return (ft_putendl_fd("cd: invalid arguments or env", 2),
			set_and_return_code(var, 1));
	if (echo_strlen(cmd) == 2)
	{
		result = chdir(cmd[1]);
		if (result == 0)
			update_pwd(cmd[1], var);
		else
			return (perror(cmd[1]), set_and_return_code(var, 1));
	}
	else if (echo_strlen(cmd) == 1)
		return (set_and_return_code(var, 0));
	else
		return (ft_putendl_fd("cd: too many arguments", 2),
			set_and_return_code(var, 1));
	return (0);
}
