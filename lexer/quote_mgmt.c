/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:27 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/14 10:52:21 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Copies string into a new string, char by char.
 * Important: Ignores first and last quote symbol found. */
char	*stirng_quote_copy(char *new_str, char *str, int first, int last)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (str[++i])
	{
		if (i == first || i == last)
			;
		else
			new_str[++j] = str[i];
	}
	new_str[++j] = '\0';
	return (new_str);
}

/** PURPOSE : Copies string into a new string, char by char.
 * 						--ALLOCATES MEMORY--
 * Important: Ignores first and last quote symbol found. */
char	*erase_quote(char *str, char sym)
{
	int		first;
	int		last;
	int		new_lenght;
	char	*new_str;

	if (!str)
		return (NULL);
	new_lenght = ft_strlen(str) - 2;
	if (!new_lenght)
		return (NULL);
	new_str = ft_calloc(new_lenght + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	first = ft_strchr(str, sym) - str;
	last = ft_strrchr(str, sym) - str;
	return (stirng_quote_copy(new_str, str, first, last));
}

/** PURPOSE : Takes a table of strings and erases the quotes.
 * It works for both " and '. Some examples: 
 * ls "-l-a"			--> 	ltable[0] = ls, table[1] = -l-a. */
char	**remove_quote(char **table)
{
	int		i;
	int		j;
	char	*new_str;

	i = -1;
	j = -1;
	while (table[++i])
	{
		if (ft_strchr(table[i], '\"') || ft_strchr(table[i], '\''))
		{
			while (table[i][++j])
			{
				if (table[i][j] == '\"')
				{
					j = ft_strchr(table[i], '\"') - table[i];
					new_str = erase_quote(table[i], '\"');
					free(table[i]);
					table[i] = new_str;
				}
				else if (table[i][j] == '\'')
				{
					j = ft_strchr(table[i], '\'') - table[i];
					new_str = erase_quote(table[i], '\'');
					free(table[i]);
					table[i] = new_str;
				}
				
			}
			j = i;
		}
	}
		//printf("%s\n", table[i]);
	return (table);
}
