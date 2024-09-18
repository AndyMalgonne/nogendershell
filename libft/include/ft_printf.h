/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:34:49 by amalgonn          #+#    #+#             */
/*   Updated: 2024/06/10 08:57:52 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

int	print_char(int fd, char c);
int	print_string(int fd, char *s);
int	print_num(int fd, int nb);
int	putnbr_base(int fd, unsigned long nbr, char *base);
int	print_ptr(int fd, unsigned long nbr, char *base);

int	ft_printf(const char *input, ...);
int	ft_dprintf(int fd, const char *input, ...);

#endif
