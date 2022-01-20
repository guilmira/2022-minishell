/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 08:47:17 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/20 15:24:59 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO, : thing like [echo "hola ' "] must work and its not working at the moment

/** PURPOSE : Reads string and evaluates if the char "quotes" is unclosed. */
int	non_closed_quote(char *line, char quotes)
{
	int	i;
	int	j;
	int	not_closed;

	i = -1;
	j = -1;
	not_closed = 0;
	while (line[++i])
	{
		if (line[i] == quotes)
		{
			not_closed++;
			j = i;
			while (line[++j])
			{
				if (line[j] == quotes)
				{
					not_closed = 0;
					break ;
				}
			}
			if (not_closed)
				return (not_closed);
			else
				i = j;
		}
	}
	return (not_closed);
}
