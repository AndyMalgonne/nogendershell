/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:19:22 by amalgonn          #+#    #+#             */
/*   Updated: 2023/11/14 16:56:25 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*d;

	d = *lst;
	while (*lst)
	{
		d = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = d;
	}
}
