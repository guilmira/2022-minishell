/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:13:28 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/16 08:57:58 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** PURPOSE : Counts words separated by char (i.e ' ', '|', ...).
 * Note that input string is expected to be trimmed. */
static int	word_count(char const *s, char c)
{
	int	i;
	int	words;

	if (!s[0])
		return (0);
	words = 1;
	i = -1;
	while (s[++i])
	{
		if (s[i] == c && s[i + 1] != c)
			words++;
	}
	return (words);
}

/** PURPOSE : Main body of the split. Allocates mem for strings
 * and places them in table.
 * 1. Moves through string.
 * 2. Detects character and allocates mem for the substring.
 * 3. Fills last place of the table with pointer to NULL. */
static char	**allocate(char *str, char **table, char c)
{
	int		i;
	int		w;
	int		start;

	i = -1;
	w = 0;
	start = 0;
	while (str[++i])
	{
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
 * 1. Trims the string at both ends.
 * 2. Allocates enough memory in table[w] by counting words in the string.
 * 3. Fills table and frees trimmed string. */
char	**ft_split(char const *s, char c)
{
	char	**table;
	char	*str;
	char	new_set[2];

	new_set[0] = c;
	new_set[1] = '\0';
	str = ft_strtrim(s, new_set);
	if (!str)
		return (NULL);
	table = (char **) ft_calloc((word_count(str, c) + 1), sizeof(*table));
	if (!table)
		return (NULL);
	table = allocate(str, table, c);
	free(str);
	return (table);
}
