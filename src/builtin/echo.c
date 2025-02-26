/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:17:34 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/26 14:00:01 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nb_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static void	check_and_flag(char **args, int *i, int *flag)
{
	int	j;

	if (!args[*i])
		return ;
	while (nb_args(args) > 1 && args[*i] && args[*i][0] == '-' && \
	args[*i][1] == 'n')
	{
		j = 1;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] != '\0')
			break ;
		*flag = 1;
		(*i)++;
	}
}

static int	write_newline_if_no_flag(int flag, t_var *var)
{
	ssize_t	write_ret;

	if (!flag)
	{
		write_ret = write(STDOUT_FILENO, "\n", 1);
		if (write_ret == -1)
			return (perror("echo: write error"), set_and_return_code(var, 1));
	}
	return (set_and_return_code(var, 0));
}

static int	write_args(char **args, int i, t_var *var)
{
	ssize_t	write_ret;

	while (args[i])
	{
		write_ret = write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (write_ret == -1)
			return (perror("echo: write error"), set_and_return_code(var, 1));
		if (args[i + 1])
		{
			write_ret = write(STDOUT_FILENO, " ", 1);
			if (write_ret == -1)
				return (perror("echo: write error"),
					set_and_return_code(var, 1));
		}
		i++;
	}
	return (0);
}

int	bi_echo(char **args, t_var *var)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (!var)
		return (1);
	check_and_flag(args, &i, &flag);
	if (write_args(args, i, var) != 0)
		return (1);
	if (!flag && write_newline_if_no_flag(flag, var) != 0)
		return (1);
	return (set_and_return_code(var, 0));
}
