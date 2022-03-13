/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:14:49 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/13 08:53:50 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Checks if line only has spaces. */
static int	only_spaces(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] != ' ')
			return (0);
	return (1);
}

/** PURPOSE : Checks if line only has spaces. */
static int	only_quotes(char *line)
{
	int	i;

	i = 0;
	while (ft_isspaces(line[i]))
		i++;
	if (is_quote(line[i]) && !line[1])
		return (1);
	if (is_quote(line[i]) && is_quote(line[i + 1]) && !is_quote(line[i + 2]))
		return (1);
	return (0);
}

/** PURPOSE : Checks for symbols that are not specified. */
static int	non_specified_char(char z)
{
	return (z == ';' || z == ':' || z == '\\');
}

/** PURPOSE : First filter of command line. */
int	pre_filter_simple(char *line)
{
	if (!line[0])
		return (1);
	if (only_spaces(line))
		return (1);
	if (only_quotes(line))
	{
		printf("Empty quotes, command line invalid.\n");
		return (1);
	}
	if (non_specified_char(line[0]))
		return (1);
	return (0);
}
