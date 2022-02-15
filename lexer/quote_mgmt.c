/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:27 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/15 13:07:49 by guilmira         ###   ########.fr       */
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
	if (new_lenght < 1)
		return (NULL);
	new_str = ft_calloc(new_lenght + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	first = ft_strchr(str, sym) - str;
	last = ft_strrchr(str, sym) - str;
	return (stirng_quote_copy(new_str, str, first, last));
}

int	needs_remove(char *str)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			if (ft_strchr(&str[i + 1], '"'))
				return (1);
		}
		else if (str[i] == '\'')
		{
			if (ft_strchr(&str[i + 1], '\''))
				return (1);
		}
	}
	return (0);
}


/** PURPOSE : Takes a table of strings and erases the quotes.
 * It works for both " and '. Some examples: 
 * ls "-l-a"			--> 	ltable[0] = ls, table[1] = -l-a. */
char	**remove_quote(char **table)
{
	int		i;
	int		j;
	char	*new_str;
	char	*str;
//"hola'"
	i = -1;
	j = -1;
	new_str = NULL;
	str = NULL;
	while (table[++i])
	{
		str = table[i];
		while (needs_remove(str))
		{
			if (ft_strchr(str, '"') && ft_strchr(str, '\''))
			{
				if (ft_strchr(str, '"') > ft_strchr(str, '\''))
				{
					new_str = erase_quote(str, '\'');
					free(str);
					table[i] = new_str;
					str = advance_line_quotes(new_str, '\'');
				}
				else
				{
					new_str = erase_quote(str, '"');
					free(str);
					table[i] = new_str;
					str = advance_line_quotes(new_str, '"');
				}
			}

			if (ft_strchr(str, '"'))
				{
					new_str = erase_quote(str, '"');
					free(str);
					table[i] = new_str;
					str = advance_line_quotes(new_str, '"');
				}


		}
	}
	return (table);
	
}
