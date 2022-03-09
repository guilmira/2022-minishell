/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_erase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:46:53 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 13:36:21 by guilmira         ###   ########.fr       */
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

/** PURPOSE : Cleans quotes from string.
 * Expects the string that has been previously treated.
 * As in "example". */
static char	*clean_quotes(char *str)
{
	char	*tmp;
	char	*new_str;

	tmp = NULL;
	new_str = NULL;
	if (is_quote(str[0]) && is_quote(str[1]) && !str[2])
		tmp = ft_strdup(" ");
	if (str[0] == SINGLE)
		new_str = ft_strtrim(str, "'");
	else if (str[0] == DOUBLE)
		new_str = ft_strtrim(str, "\"");
	else
		new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);
	if (new_str && tmp)
		free (tmp);
	return (new_str);
}

/** PURPOSE : Function that handles quote detecting and erases them. */
static char	*build_line_from_list(t_list *list)
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

/** PURPOSE : Function that handles quote detecting and erases them. */
char	*ultra_quotes(char *str)
{
	int		i;
	int		t;
	char	*new_str;
	t_list	*list;

	i = 0;
	t = 0;
	list = NULL;
	new_str = NULL;
	while (str[i])
	{
		if (is_quote(str[i]))
			i = advance_to_next_quote(str, i);
		else
		{
			while (str[i] && !is_quote(str[i]))
				i++;
		}
		fix_previous_line(str, t, i, &list);
		t = i;
	}
	new_str = build_line_from_list(list);
	
	ft_fullclear(list);
	return (new_str);
}
