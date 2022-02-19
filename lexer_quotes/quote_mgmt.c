/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:27 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/19 11:34:06 by guilmira         ###   ########.fr       */
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
		{
			if (ft_strchr(&str[i + 1], SINGLE))
				return (1);
		}
	}
	return (0);
}

/** PURPOSE : Cleans quotes from string.
 * Expects the string that has been previously treated.
 * As in "example". */
char	*clean_quotes(char *str)
{
	char	*new_str;

	if (str[0] == SINGLE)
		new_str = ft_strtrim(str, "'");
	else if (str[0] == DOUBLE)
		new_str = ft_strtrim(str, "\"");
	else
		new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);
	return (new_str);
}

char	*build_line_form_list(t_list *list)
{
	char	*str;
	char	*tmp;
	char	*fragment;

	str = NULL;
	fragment = NULL;
	tmp = NULL;
	str = clean_quotes(list->content);
	list = list->next;
	while (list)
	{
		tmp = str;
		fragment = clean_quotes(list->content);
		str = ft_strjoin(tmp, fragment);
		if (!str)
			return (NULL);
		free(tmp);
		free(fragment);
		list = list->next;
	}
	return (str);
}

char	*ultra_quotes(char *str)
{
	int		i;
	int		t;
	char	*new_str;
	t_list	*list;

	list = NULL;
	new_str = NULL;
	i = 0;
	t = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			i = advance_to_next_quote(str, i);
			fix_previous_line(str, t, i, &list);
			t = i + 1;
		}
		else
		{
			while (str[i] && !is_quote(str[i]))
				i++;
			fix_previous_line(str, t, i, &list);
			t = i;
		}
		t = i;
	}
	new_str = build_line_form_list(list);
	return (new_str);
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
