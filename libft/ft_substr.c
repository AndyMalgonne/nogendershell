/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:35:16 by amalgonn          #+#    #+#             */
/*   Updated: 2023/11/14 13:20:40 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	strl;

	strl = ft_strlen(s);
	if (!s)
		return (NULL);
	i = start;
	j = 0;
	if (len > strl - start)
		len = strl - start;
	if (start > strl)
	{
		str = malloc(1);
		str[j] = '\0';
		return (str);
	}
	str = ((char *)malloc(len + 1));
	if (!str)
		return (NULL);
	while (i < strl && j < len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}

// int main(int argc, char const *argv[])
// {
// 	char * s = ft_substr("tripouille", 100, 1);
// 	printf(".%s\n", s);
// 	free(s);
// 	return 0;
// }