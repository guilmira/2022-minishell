/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 08:47:17 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:19 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


//TOCAR ESTE ARCHIVO HACE MUY SENCILO QUe DE SEG FAULT , PERO NO SERA SENCILLO DE DETECTAR
/** PURPOSE : Reads string and evaluates if the char "collons" is unclosed. */
int	non_closed_collons(char *line, char collons)
{
	int	i;
	int	j;
	int	not_closed;

	i = -1;
	j = -1;
	not_closed = 0;
	while (line[++i])
	{
		if (line[i] == collons)
		{
			not_closed++;
			j = i;
			while (line[++j])
			{
				if (line[j] == collons)
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
	return(not_closed);
}