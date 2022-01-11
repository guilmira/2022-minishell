/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 04:26:02 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/11 10:27:20 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Checks for symbols that are not specified. */
static int	non_specified_char(char z)
{
	return (z == ';' || z == ':' || z == '\\');
}

//TODO should it identify '\'??



/** PURPOSE : Boolean, checks if first char is just a symbol. */
static int	only_symbol(char *line)
{
	char	z;

	z = line[0];
	return (z == '|' || z == '<' || z == '>' || z == '-');
}

//TODO FUNCT
// echo what|ls YEs
// echo| YES
// echo | wc | YES



//no vale esto: skajhfkjashgf | //      | ls -la
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
	if (non_closed_quote(line, '"') || non_closed_quote(line, '\'') ) //TODO: not finished, exlained in function
	{
		printf("Quotes (\" or '') must be closed\n");
		return (1);
	}
	if (pipe_not_continued())
	{
		printf("Insert command after pipe\n");
		return (1);
	}
	return (0);
}