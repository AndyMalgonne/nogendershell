/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:54:08 by amalgonn          #+#    #+#             */
/*   Updated: 2023/11/13 15:19:49 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	write (fd, s, ft_strlen(s));
}

// int main()
// {
// 	char *s = "coucou";
// 	int test = open("cc.txt", O_RDWR);
// 	ft_putstr_fd(s, test);
// }
