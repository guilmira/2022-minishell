/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 04:26:02 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/16 11:22:40 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Simple parser of command line. */
int	pre_filter(char *line)
{
	if (pre_filter_simple(line))
		return (1);
	if (pre_filter_advanced(line))
		return (1);
	return (0);
}
