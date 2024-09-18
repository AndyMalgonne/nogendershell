/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:56:05 by marvin            #+#    #+#             */
/*   Updated: 2023/11/15 11:56:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i[2];

	i[1] = 0;
	tab = ft_calloc(sizeof(char *), count_words(s, c) + 1);
	if (!tab)
		return (NULL);
	while (*s)
	{
		i[0] = 0;
		while (*s && *s == c)
			s++;
		while (s[i[0]] && s[i[0]] != c)
			i[0]++;
		if (*s && i[0])
		{
			tab[i[1]] = ft_substr(s, 0, i[0]);
			if (!tab[i[1]++])
				return (ft_fsplit(tab));
		}
		s = s + i[0];
	}
	tab [i[1]] = (NULL);
	return (tab);
}

// int	main()
// {
// 	printf("%s", ft_split("  tripouille  42  ", ' '));
// }