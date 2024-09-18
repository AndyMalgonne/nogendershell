/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:12:06 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/06/12 18:23:03 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_fsplit(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return (NULL);
	while (split[i])
		free(split[i++]);
	free (split);
	return (NULL);
}
