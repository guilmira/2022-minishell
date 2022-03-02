/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:27 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/02 13:48:21 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Identifies if strings needs quote remover. */
static int	needs_remove(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == DOUBLE)
		{
			if (ft_strchr(&str[i + 1], DOUBLE))
				return (1);
		}
		else if (str[i] == SINGLE)
			if (ft_strchr(&str[i + 1], SINGLE))
				return (1);
	}
	return (0);
}

/** PURPOSE : Takes a table of strings and erases the quotes.
 * It works for both " and '. Some examples: 
 * ls "-l-a"			--> 	ltable[0] = ls, table[1] = -l-a. */
char	**remove_quote(char **table)
{
	int		i;
	char	*new_str;
	char	*str;

	i = -1;
	new_str = NULL;
	str = NULL;
	while (table[++i])
	{
		str = table[i];
		if (needs_remove(str))
		{
			new_str = ultra_quotes(str);
			free(str);
			table[i] = new_str;
		}
	}
	return (table);
}
