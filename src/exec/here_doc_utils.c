/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andytropmimi <andytropmimi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:38:10 by andytropmim       #+#    #+#             */
/*   Updated: 2025/01/07 14:56:49 by andytropmim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*r_name(unsigned char r_bytes[], const char alpha[], \
int alpha_size, int size)
{
	char	*file;
	int		i;

	file = ft_calloc(size, sizeof(char));
	if (!file)
		return (NULL);
	i = -1;
	while (i++ < 3)
		file[i] = alpha[r_bytes[i] % alpha_size];
	file[3] = '\0';
	return (file);
}

int	get_random_bytes(unsigned char random_bytes[], int size)
{
	int	fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, random_bytes, size) != size)
		return (close(fd), -1);
	close(fd);
	return (0);
}

void	increment_random_bytes(unsigned char random_bytes[], int alphanum_size)
{
	int	i;

	i = 3;
	while (i-- >= 0)
	{
		random_bytes[i]++;
		random_bytes[i] %= alphanum_size;
		if (random_bytes[i] != 0)
			break ;
	}
}
