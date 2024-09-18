/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andytropmimi <andytropmimi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:26:01 by amalgonn          #+#    #+#             */
/*   Updated: 2023/11/17 10:27:03 by andytropmim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	if (s == 0)
		return (NULL);
	while (i < n)
	{
		if (((unsigned char *)s)[i] == ((unsigned char) c))
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

// void	main()
// {
// 	char truc[]="hello world";
// 	printf("%s",(char *)ft_memchr(truc,'o', 5));
// }