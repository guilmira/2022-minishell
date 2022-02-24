/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_auxiliars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:06:44 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/16 12:34:26 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Detects wheter the char is a quote. */
int	is_quote(char symbol)
{
	if (symbol == SINGLE || symbol == DOUBLE)
		return (1);
	return (0);
}

/** PURPOSE : General function. Detects first quotes and 
 * advances string to next position after second quote. */
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

/** PURPOSE : Advance to INMIDATE next quote. */
int	advance_to_next_quote(char *line, int i)
{
	if (!line)
		return (i);
	if (is_quote(line[i]))
	{
		if (line[i] == SINGLE)
		{
			while (line[++i] != SINGLE)
				;
			return (++i);
		}
		else if (line[i] == DOUBLE)
		{
			while (line[++i] != DOUBLE)
				;
			i++;
		}
	}
	return (i);
}