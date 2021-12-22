/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 04:26:02 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/22 04:40:57 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int only_symbol(char *line)
{
	char z;

	z = line[0];
	return (z == '|' || z == '<' || z == '>');
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
	return (0);
}