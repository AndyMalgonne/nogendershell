/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:10:58 by amalgonn          #+#    #+#             */
/*   Updated: 2024/09/18 14:25:23 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	putnbr_base(int fd, unsigned long nbr, char *base)
{
	int				size_base;
	int				i;

	size_base = 0;
	i = 1;
	if (*base == 0)
		return (0);
	while (base[size_base])
		size_base++;
	if (nbr / size_base)
		i += putnbr_base(fd, nbr / size_base, base);
	ft_putchar_fd(base[nbr % size_base], fd);
	return (i);
}

int	print_ptr(int fd, unsigned long nbr, char *base)
{
	if (nbr == 0)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	return (putnbr_base(fd, nbr, base) + 2);
}
