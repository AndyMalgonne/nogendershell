/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:30:59 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/21 23:59:11 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(void)
{
	printf("bi_pwd\n");
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		return (ft_putendl_fd(cwd, 1), 0);
	else
		return (ft_putendl_fd(strerror(errno), 2), 1);
}
