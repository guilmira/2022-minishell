/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 04:26:02 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/06 15:54:23 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Checks for symbols that are not specified. */
static int	non_specified_char(char z)
{
	return (z == ';' || z == ':' || z == '\\');
}

//should it identify '\'??

/** PURPOSE : Reads string and evaluates if there are collons unclosed. */
static int	non_closed_collons(char *line, char collons)
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
				if (!line[j] && not_closed)
					break ;
			}
			if (line[j + 1])
				i = j + 1;
			else
				return(not_closed);
		}
	}
	return(not_closed);
}

/** PURPOSE : Boolean, checks if first char is just a symbol. */
static int	only_symbol(char *line)
{
	char	z;

	z = line[0];
	return (z == '|' || z == '<' || z == '>' || z == '-');
}

//TODO FUNCT
// echo "what|dssg" NO
// echo| YES
// echo | wc | YES
int pipe_not_continued(void)
{
	return (0);
}

/** PURPOSE : Simple parser of command line as soon
 * as its read. */
int	pre_filter(char *line)
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
	if (non_closed_collons(line, '"') || non_closed_collons(line, '\'') )
	{
		printf("Collons must be closed\n");
		return (1);
	}
	if (pipe_not_continued())
	{
		printf("Insert command after pipe\n");
		return (1);
	}
	return (0);
}