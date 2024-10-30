/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:02:33 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/10/30 18:17:01 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
}

//int	main(int ac, char **av)
//{
//	char	*rl;

//	(void)av;
//	if (ac != 1)
//		return (0);
//	while (1)
//	{
//		rl = readline("\033[0;36mnogender\033[0;35mshell > \033[0m");
//		if (!rl)
//			break ;
//		if (rl && *rl)
//			add_history(rl);
//		if (ft_strncmp(rl, "exit", 4) == 0)
//		{
//			free(rl);
//			break ;
//		}
//		if (ft_strncmp(rl, "echo", 4) == 0)
//		{
//			ft_printf("%s\n", rl + 5);
//			free(rl);
//			continue ;
//		}
//		if (ft_strncmp(rl, "clear", 5) == 0)
//		{
//			ft_printf("\033[H\033[J");
//			free(rl);
//			continue ;
//		}
//		else
//		{
//			ft_printf("\033[0;35mnogender\033[0;36mshell:\033[0m \
//command not found: %s\n", rl);
//			free(rl);
//		}
//	}
//	return (0);
//}
