/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 08:47:17 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/07 18:04:02 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// OBSOLETO PARA BORRAR
/** PURPOSE : Reads string and evaluates if the char "quotes" is unclosed. */
/* static int	non_closed_quote(char *line, char quotes)
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
				if (line[j] == quotes)
					break ;
			if (line[j] == quotes)
				not_closed = 0;
			if (not_closed)
				return (not_closed);
			else
				i = j;
		}
	}
	return (not_closed);
} */

/** PURPOSE : Checks for a command line that has " and ' . */
/* static char	*double_quote_filter(char *line, int flag)
{
	if (ft_strchr(line, DOUBLE) > ft_strchr(line, SINGLE))
	{
		if (non_closed_quote(line, SINGLE))
		{
			flag++;
			return (NULL);
		}
		line = advance_line_quotes(line, SINGLE);
	}
	else
	{
		if (non_closed_quote(line, DOUBLE))
		{
			flag++;
			return (NULL);
		}
		line = advance_line_quotes(line, DOUBLE);
	}
	return (line);
} */

/** PURPOSE : Prevent unclosed quotes in command line. */
/* int	quotes_filter(char *line)
{
	int	flag;

	flag = 0;
	while (ft_strchr(line, DOUBLE) || ft_strchr(line, SINGLE))
	{
		if ((ft_strchr(line, DOUBLE) && ft_strchr(line, SINGLE)))
		{
			line = double_quote_filter(line, flag);
			if (flag)
				return (1);
			if (!line)
				return (0);
		}
		else
		{
			if (non_closed_quote(line, SINGLE))
				return (1);
			if (non_closed_quote(line, DOUBLE))
				return (1);
			line = advance_line_quotes(line, DOUBLE);
			line = advance_line_quotes(line, SINGLE);
		}
	}
	return (0);
} */

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
