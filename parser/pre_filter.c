/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 04:26:02 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/12 14:02:13 by guilmira         ###   ########.fr       */
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
		if (!ft_strcmp(table[i], "\"") || !ft_strcmp(table[i], "\'"))
			flag++;
	ft_free_split(table);
	if (flag)
		return (1);
	else
		return (0);
}

char *advance_line_quotes(char *line, char quote)
{
	char	*advanced_line;

	advanced_line = NULL;
	if (!ft_strchr(line, quote))
		return (line);
	advanced_line = ft_strchr(line, quote) + 1;
	advanced_line = ft_strchr(advanced_line, quote) + 1;
	return (advanced_line);
}

char *double_quote_filter(char *line, int flag)
{
	if (ft_strchr(line, '"') > ft_strchr(line, '\'')) //tratar las simples
	{
		if (non_closed_quote(line, '\''))
		{
			flag++;
			return (NULL);
		}
		line = advance_line_quotes(line, '\'');
	}
	else
	{
		if (non_closed_quote(line, '"'))
		{
			flag++;
			return (NULL);
		}
		line = advance_line_quotes(line, '"');
	}
	return (line);
}

//hacer funcion que solo quite las comillas del exteiror
int	quotes_filter(char *line)
{
	int	flag;

	flag = 0;
	while (ft_strchr(line, '"') || ft_strchr(line, '\''))
	{
		if ((ft_strchr(line, '"') && ft_strchr(line, '\'')))
		{
			line = double_quote_filter(line, flag);
			if (flag)
				return (1);
			if (!line)
				return (0);
		}
		else
		{
			if (non_closed_quote(line, '\''))
				return (1);
			if (non_closed_quote(line, '"'))
				return (1);
			line = advance_line_quotes(line, '"');
			line = advance_line_quotes(line, '\'');
		}
	}
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
	if (quotes_filter(line))
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
