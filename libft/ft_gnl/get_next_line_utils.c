/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:37:09 by amalgonn          #+#    #+#             */
/*   Updated: 2025/01/20 21:57:01 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strnjoin(char *s1, char const *s2, size_t new_line)
{
	char		*str;
	size_t		i;
	size_t		j;

	str = (char *)malloc(ft_strlen(s1) + new_line + 1);
	if (!s1 || !s2 ||!(str))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && j < new_line)
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
