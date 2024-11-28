/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:41:34 by gmoulin           #+#    #+#             */
/*   Updated: 2024/11/28 17:01:31 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_tokenizing(char **rl, t_token **head)
{
	t_token	*n_token;

	if (is_bi_echo(*rl))
		n_token = new_token(BI_ECHO, ft_strdup("echo"));
	else if (is_bi_cd(*rl))
		n_token = new_token(BI_CD, ft_strdup("cd"));
	else if (is_bi_pwd(*rl))
		n_token = new_token(BI_PWD, ft_strdup("pwd"));
	else if (is_bi_export(*rl))
		n_token = new_token(BI_EXPORT, ft_strdup("export"));
	else if (is_bi_unset(*rl))
		n_token = new_token(BI_UNSET, ft_strdup("unset"));
	else if (is_bi_env(*rl))
		n_token = new_token(BI_ENV, ft_strdup("env"));
	else if (is_bi_exit(*rl))
		n_token = new_token(BI_EXIT, ft_strdup("exit"));
	else
		return (0);
	if (!n_token)
		return (0);
	append_token(head, n_token);
	while (**rl && !is_space_tab(**rl))
		(*rl)++;
	return (1);
}
