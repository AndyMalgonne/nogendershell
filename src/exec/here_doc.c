/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:09:35 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/01/31 14:20:19 by abasdere         ###   ########.fr       */
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

int	write_to_heredoc(int fd, const char *del)
{
	char	*gnl;

	ft_printf("here_doc > ");
	gnl = get_next_line(0);
	while (gnl)
	{
		if (ft_strncmp(gnl, del, ft_strlen(del) + 1) == 0)
			break ;
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

int	get_here_doc(char *del)
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
		return (free(del), close(fd[0]), close(fd[1]), -1);
	if (write_to_heredoc(fd[0], del) < 0)
		return (free(del), close(fd[0]), close(fd[1]), -1);
	return (free(del), close(fd[0]), fd[1]);
}
