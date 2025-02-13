/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_iofile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:34:28 by gmoulin           #+#    #+#             */
/*   Updated: 2025/02/13 14:44:05 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_iofile	*new_iofile(t_iotype type, const char *value)
{
	t_iofile	*io;

	io = (t_iofile *)malloc(sizeof(t_iofile));
	if (!io)
		return (NULL);
	io->type = type;
	io->value = NULL;
	if (value)
	{
		io->value = ft_strdup(value);
		if (!io->value)
			return (free(io), NULL);
	}
	io->next = NULL;
	return (io);
}

void	append_iofile(t_iofile **head, t_iofile *new)
{
	t_iofile	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_iofile(t_iofile **io)
{
	if (*io)
	{
		if ((*io)->value)
			free_to_null(&((*io)->value));
		free_iofile(&(*io)->next);
		free_to_null(io);
	}
}

const char	*iottostr(t_iotype type)
{
	static const char	*token_type_str[] = {
		"INFILE",
		"HEREDOC",
		"OUTFILE_TRUNC",
		"OUTFILE_APPEND",
	};

	if (type < 0 || type >= sizeof(token_type_str) / sizeof(token_type_str[0]))
		return ("WTF");
	return (token_type_str[type]);
}
