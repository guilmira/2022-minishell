/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0dollar_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:21:40 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/02 10:06:02 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Advance to INMIDATE next piece of fragment. */
int	advance_to_next_fragment(char *line, int i)
{
	if (!line)
		return (i);
	while (line[++i])
		if (line[i] == EXPAN || line[i] == ' ' || line[i] == SINGLE)
			break;
	return (i);
}


char	*build_from_list(t_list *list)
{
	char	*str;
	char	*tmp;
	char	*fragment;

	str = NULL;
	fragment = NULL;
	tmp = NULL;
	str = ft_strdup(list->content);
	list = list->next;
	while (list)
	{
		tmp = str;
		str = ft_strjoin(tmp, list->content);
		if (!str)
			return (NULL);
		free(tmp);
		list = list->next;
	}
	return (str);
}

int	necessary_expansion(char first, char second)
{
    if (first == EXPAN)
        if (second != SINGLE && second != DOUBLE)
            return (1);
    return (0);
}

static char	*get_fragment(char *str)
{
	int		i;
	char	*new_str;

	new_str = NULL;
	i = 0;
	while (str[++i])
	{
		//printf("cahar %c\n", str[i]);
		if (!str[i + 1])
			new_str = ft_substr(str, 1, i);
		else if (str[i] == ' ' || str[i] == EXPAN || str[i] == SINGLE)
		{
			new_str = ft_substr(str, 1, i - 1);
			break;
		}
	}
	return (new_str);
}

char	*ultra_expansion(char *str, t_arguments *args)
{
	int		i;
	int		t;
	char	*new_str;
	char	*fragment;
	char	*value;
	t_list	*list;


	i = 0;
	t = 0;
	list = NULL;
	new_str = NULL;
	fragment = NULL;
	value = NULL;
	while (str[i])
	{
		if (str[i] == SINGLE)
		{
			i = advance_to_next_quote(str, i);
			fix_previous_line(str, t, i, &list);
			t = i + 1;
		}
		else if (str[i] == EXPAN)
		{
			fragment = get_fragment(&str[i]);
			printf("fragment %s\n", fragment);
			i = advance_to_next_fragment(str, i);
			printf("EXPANDIR\n");
			t = i + 1;
			value = get_env_var(args->envp, fragment);
			printf("value: %s\n", value);
			ft_lstadd_back(&list, ft_lstnew(value));

			free(fragment);
		}
		else
		{
			while (str[i] && str[i] != EXPAN && str[i] != SINGLE)
				i++;
			fix_previous_line(str, t, i, &list);
			t = i;
		}
		t = i;
	}
	new_str = build_from_list(list);
	ft_fullclear(list);
	return (new_str);
}


static int	needs_expansion(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == SINGLE)
		{
			i = advance_to_next_quote(str, i);
			if (!str[i])
				break;
		}
		else if (str[i] == EXPAN && str[i + 1])
			if (str[i + 1] != SINGLE && str[i + 1] != DOUBLE)
				return (1);
	}
	return (0);
}

/** PURPOSE : Substitute de variable preceeded by the 
 * symbol $ for the corresponding environment variable. */
char	**dollar_expansion(char **table, t_arguments *args)
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
		if (needs_expansion(str))
		{
			new_str = ultra_expansion(str, args);
			free(str);
			table[i] = new_str;
		}
	}
	return (table);
}