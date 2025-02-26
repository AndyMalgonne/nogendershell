/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:09:35 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/26 19:25:23 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_heredoc_file(void)
{
	char			*file;
	const char		alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int				alphanum_size;
	unsigned char	random_bytes[3];
	int				size;

	alphanum_size = sizeof(alphanum) - 1;
	size = 5;
	if (get_random_bytes(random_bytes, 3) < 0)
		return (NULL);
	file = r_name(random_bytes, alphanum, alphanum_size, size);
	if (!file)
		return (NULL);
	while (access(file, F_OK) == 0)
	{
		free(file);
		increment_random_bytes(random_bytes, alphanum_size);
		file = r_name(random_bytes, alphanum, alphanum_size, size);
		if (!file)
			return (NULL);
	}
	return (file);
}

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
	while (value[j] && !is_space_tab(value[j])
		&& value[j] != '$' && value[j] != '"')
		j++;
	key = ft_substr(value, i + 1, j - (i + 1));
	if (!key)
		return (NULL);
	env_value = get_env_value(env, key);
	printf("Replacing $%s with %s\n", key, env_value); // Debugging line
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

int	expand_heredoc_value(char *value, t_var *var)
{
	size_t	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			if (value[i + 1] == '?')
				value = replace_exit_status(value, var->code, i);
			else
				value = replace_env_value(value, var->env, i);
			if (!value)
				return (0);
			i = 0;
		}
		else
			i++;
	}
	return (1);
}

int	write_to_heredoc(int fd, const char *del, t_var *var)
{
	char	*gnl;

	ft_printf("here_doc > ");
	gnl = get_next_line(0);
	while (gnl)
	{
		if (ft_strncmp(gnl, del, ft_strlen(del) + 1) == 0)
			break ;
		expand_heredoc_value(gnl, var);
		ft_putstr_fd(gnl, fd);
		free(gnl);
		ft_printf("here_doc > ");
		gnl = get_next_line(0);
	}
	if (!gnl)
		return (-1);
	free(gnl);
	return (0);
}

int	get_here_doc(char *del, t_var *var)
{
	char	*file;
	int		fd[2];

	del = ft_strjoin(del, "\n");
	if (!del)
		return (-1);
	file = find_heredoc_file();
	if (!file || !del)
		return (free(del), free(file), -1);
	fd[0] = open(file, O_WRONLY | O_CREAT, 0644);
	fd[1] = open(file, O_RDONLY);
	(unlink(file), free(file));
	if (fd[0] < 0 || fd[1] < 0)
		return (free(del), mclose(&fd[0]), mclose(&fd[1]), -1);
	if (write_to_heredoc(fd[0], del, var) < 0)
		return (free(del), mclose(&fd[0]), mclose(&fd[1]), -1);
	return (free(del), mclose(&fd[0]), fd[1]);
}

int	process_heredoc(t_tree *cmd, t_fds *fds, t_var *var)
{
	t_iofile	*io;

	io = cmd->io;
	while (io)
	{
		if (io->type == HEREDOC)
		{
			set_signals(&handle_child_sigint, SIG_IGN);
			if (fds->heredocfd > 0)
				mclose(&(fds->heredocfd));
			fds->heredocfd = get_here_doc(io->value, var);
			if (fds->heredocfd < 0)
				return (mclose(&fds->heredocfd), -1);
		}
		io = io->next;
	}
	return (0);
}
