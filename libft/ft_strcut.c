/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andytropmimi <andytropmimi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:57:45 by andytropmim       #+#    #+#             */
/*   Updated: 2025/02/10 14:36:33 by andytropmim      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(const char *str, char stop)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != stop)
		i++;
	return (ft_substr(str, 0, i));
}
