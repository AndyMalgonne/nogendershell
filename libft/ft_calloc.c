/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:53:42 by amalgonn          #+#    #+#             */
/*   Updated: 2023/11/16 14:58:02 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			x;

	x = nmemb * size;
	if (size != 0 && !(x / size == nmemb))
		return (NULL);
	ptr = malloc(x);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, x);
	return (ptr);
}
