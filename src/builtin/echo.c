/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:17:34 by andymalgonn       #+#    #+#             */
/*   Updated: 2025/02/25 21:03:20 by gmoulin          ###   ########.fr       */
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

static int	handle_write_error(t_var *var)
{
	error(var, "echo: write error", 1);
	return (1);
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
			return (handle_write_error(var));
	}
	return (0);
}

int	bi_echo(char **args, t_var *var)
{
	int		i;
	int		flag;
	int		write_ret;

	i = 1;
	flag = 0;
	check_and_flag(args, &i, &flag);
	while (args[i])
	{
		write_ret = write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (write_ret == -1)
			return (handle_write_error(var));
		if (args[i + 1])
		{
			write_ret = write(STDOUT_FILENO, " ", 1);
			if (write_ret == -1)
				return (handle_write_error(var));
		}
		i++;
	}
	if (!flag)
		if (write_newline_if_no_flag(flag, var) != 0)
			return (1);
	return (0);
}
