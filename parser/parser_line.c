/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 04:26:02 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/22 07:38:43 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int non_specified_char(char z)
{
	return (z == ';' || z == ':' || z == '\\');
}

//should it identify '\'??

static int non_closed_collons(char *line)
{
	int	i;
	int	j;
	int not_closed;

	i = -1;
	j = -1;
	not_closed = 0;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			not_closed++;
			j = i;
			while (line[++j])
			{
				if (line[j] == '"')
				{
					not_closed = 0;
					break;
				}
				if (!line[j] && not_closed)
					break;
			}
			if (line[j + 1])
				i = j + 1;
			else
				return(not_closed);
			
		}
	}
	return(not_closed);
}


static int only_symbol(char *line)
{
	char z;

	z = line[0];
	return (z == '|' || z == '<' || z == '>' || z == '-');
}

int	parser_line(char *line)
{
	if (!line[0])
		return (1);
	if (only_symbol(line))
	{
		printf("parse error on inital symbol\n");
		return (1);
	}
	if (non_specified_char(line[0]))
		return (1);
	if (non_closed_collons(line))
	{
		printf("Collons must be closed\n");
		return (1);
	}
	return (0);
}