/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 08:47:17 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 14:43:18 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Counts positions on a table .*/
int	count_table(char **table)
{
	int	i;

	if (!table)
		return (0);
	i = -1;
	while (table[++i])
		;
	return (i);
}

/** PURPOSE : Prevent unclosed quotes in command line. */
int	quotes_filter(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == SINGLE)
		{
			while (line[++i])
				if (line[i] == SINGLE)
					break ;
			if (line[i] != SINGLE)
				return (1);
		}
		else if (line[i] == DOUBLE)
		{
			while (line[++i])
				if (line[i] == DOUBLE)
					break ;
			if (line[i] != DOUBLE)
				return (1);
		}
	}
	return (0);
}

int	is_heredoc(char *string)
{
	if (!ft_strcmp(string, HEREDOC))
		return (1);
	return (0);
}
