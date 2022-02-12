/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 04:26:02 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/12 11:38:19 by guilmira         ###   ########.fr       */
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

//TODO function:   no vale esto: 	command | //      | ls -la
// si encontramos esto "|", no ejecutar
int	pipe_not_continued(void)
{
	return (0);
}

int	only_spaces(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] != ' ')
			return (0);
	return (1);
}

/** PURPOSE : Chech for arguments such as > " " */
static int hanging_quotes(char *line)
{
	int		i;
	int		flag;
	char	**table;
	

	table = ft_split(line, ' ');
	flag = 0;
	i = -1;
	while (table[++i])
	{
		if (!ft_strcmp(table[i], "\"") || !ft_strcmp(table[i], "\'"))
			flag++;
	}
	ft_free_split(table);
	if (flag)
		return (1);
	else
		return (0);
}

/** PURPOSE : Simple parser of command line as soon
 * as its read. */
int	pre_filter(char *line)
{
	if (!line[0])
		return (1);
	if (only_spaces(line))
		return (1);
	if (only_symbol(line))
	{
		printf("parse error on initial symbol\n");
		return (1);
	}
	if (non_specified_char(line[0]))
		return (1);
	if (non_closed_quote(line, '"') || non_closed_quote(line, '\'')) //TODO: not finished, explained in function
	{
		printf("Quotes (\" or '') must be closed\n");
		return (1);
	}
	if (pipe_not_continued())
	{
		printf("Insert command after pipe\n");
		return (1);
	}
	if (hanging_quotes(line))
	{
		printf("Incorrect quoting use. Please make sure quotes are not empty when entering commands\n");
		return (1);
	}
	return (0);
}
