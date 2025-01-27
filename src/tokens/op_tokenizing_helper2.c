/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tokenizing_helper2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:50:20 by gmoulin           #+#    #+#             */
/*   Updated: 2025/01/27 20:16:13 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_backlash(char **rl)
{
	if (is_space_tab((*rl)[1]) || !(*rl)[1])
		return (new_token(OP_BACKLASH, ft_strdup("\\")));
	return (NULL);
}
