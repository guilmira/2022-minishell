/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:38 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 13:44:08 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Ignore quotes. */
int	ignore_symbol(char *str, int position)
{
	int	i;

	i = position;
	if (str[i] == DOUBLE)
		while (str[++i] != DOUBLE)
			;
	if (str[i] == SINGLE)
		while (str[++i] != SINGLE)
			;
	return (i);
}

/** PURPOSE : Counts words separated by char (i.e ' ', '|', ...).
 * Note that input string is expected to be trimmed. */
static int	quote_word_count(char *str, char c)
{
	int	i;
	int	words;

	if (!str[0])
		return (0);
	words = 1;
	i = -1;
	while (str[++i])
	{
		i = ignore_symbol(str, i);
		if (str[i] == c && str[i + 1] != c)
			words++;
	}
	return (words);
}

/** PURPOSE : Allocates mem for strings and places them in table.
 * 1. Moves through string.
 * 2. Detects character and allocates mem for the substring.
 * 3. Fills last place of the table with pointer to NULL. */
static char	**quote_allocate(char *str, char **table, char c)
{
	int		i;
	int		w;
	int		start;

	i = -1;
	w = 0;
	start = 0;
	while (str[++i])
	{
		//printf("va por %c y %i\n", str[i], i);
		i = ignore_symbol(str, i);
		if ((str[i + 1] == c || !str[i + 1]))
		{
			if (str[i] != c)
			{
				table[w] = ft_substr(str, start, i + 1 - start);
				if (!table[w++])
					return (NULL);
			}
		}
		if (str[i + 1] == c && str[i + 2] != c)
			start = i + 2;
	}
	table[w] = NULL;
	return (table);
}

/** PURPOSE : Takes a string and loads words into an array of type table[w].
  * 						--ALLOCATES MEMORY--
 * 0. IGNORES FIRST QUOTES AS TO REPLICATE SHELL BEHAVIOUR.
 * 1. Trims the string at both ends.
 * 2. Allocates enough memory in table[w] by counting words in the string.
 * 3. Fills table and frees trimmed string. */
char	**quote_split(char const *s, char c)
{
	char	**table;
	char	*str;
	char	new_set[2];

	new_set[0] = c;
	new_set[1] = '\0';
	str = ft_strtrim(s, new_set);
	if (!str)
		return (NULL);
	table = (char **) ft_calloc((quote_word_count(str, c) + 1), sizeof(*table));
	if (!table)
		return (NULL);
	table = quote_allocate(str, table, c);
	free(str);
	return (table);
}
