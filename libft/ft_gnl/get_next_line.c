/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:24:32 by amalgonn          #+#    #+#             */
/*   Updated: 2024/08/02 18:46:34 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	read_error(int fd, char *buf)
{
	int	i;

	if (buf[0] != 0)
		return (1);
	i = read(fd, buf, BUFFER_SIZE);
	if (i > 0)
	{
		buf[i] = '\0';
		return (1);
	}
	return (0);
}

static char	*read_line_from_buffer(char *line, char *buf, int fd)
{
	int		i;

	i = 1;
	while (!(ft_strchr(line, '\n')) && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[i] = '\0';
		line = ft_strnjoin(line, buf, i);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line[2];
	int			i;

	if (read_error(fd, buf) == 0)
		return (NULL);
	line[0] = ft_strdup(buf);
	if (!line[0])
		return (NULL);
	line[0] = read_line_from_buffer(line[0], buf, fd);
	if (ft_strlen(line[0]) == 0)
		return (free(line[0]), NULL);
	line[1] = ft_strchr(line[0], '\n');
	if (line[1] != NULL)
	{
		i = line[1] - line[0] + 1;
		ft_strlcpy(buf, line[1] + 1, BUFFER_SIZE + 1);
	}
	else
	{
		i = ft_strlen(line[0]);
		ft_strlcpy(buf, "", BUFFER_SIZE + 1);
	}
	line[0][i] = '\0';
	return (line[0]);
}
