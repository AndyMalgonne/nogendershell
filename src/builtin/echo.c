/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:17:34 by andymalgonn       #+#    #+#             */
/*   Updated: 2024/11/05 11:36:57 by andymalgonn      ###   ########.fr       */
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

static int	handle_write_error(void)
{
	perror("echo: write error");
	return (1);
}

static void	check_and_flag(char **args, int *i, int *flag)
{
	int	j;

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

static int	write_newline_if_no_flag(int flag)
{
	ssize_t	write_ret;

	if (!flag)
	{
		write_ret = write(STDOUT_FILENO, "\n", 1);
		if (write_ret == -1)
			return (handle_write_error());
	}
	return (0);
}

int	bi_echo(char **args)
{
	int		i;
	int		flag;
	int		write_ret;

	i = 1;
	flag = 0;
	check_and_flag(args, &i, &flag);
	while (args[i])
	{
		write_ret = write(STDOUT_FILENO, args[i], strlen(args[i]));
		if (write_ret == -1)
			return (handle_write_error());
		if (args[i + 1])
		{
			write_ret = write(STDOUT_FILENO, " ", 1);
			if (write_ret == -1)
				return (handle_write_error());
		}
		i++;
	}
	if (!flag)
		if (write_newline_if_no_flag(flag) != 0)
			return (1);
	return (0);
}
