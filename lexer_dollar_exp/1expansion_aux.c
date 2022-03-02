/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1expansion_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 10:15:06 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/02 13:41:35 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Builds a signle string from all nodes. */
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

/** PURPOSE : Advance to INMIDATE next piece of variable. */
static int	advance_to_next_variable(char *line, int i)
{
	if (!line)
		return (i);
	while (line[++i])
		if (line[i] == EXPAN || line[i] == ' ' || line[i] == SINGLE)
			break;
	return (i);
}

/** PURPOSE : Reads a string and gets the first 
 * variable found: thisisastring$VARIABLE$SECONDVAR.
 * It will output $VARIABLE and allocate memory for it */
static char	*get_variable_onstring(char *str)
{
	int		i;
	char	*new_str;

	new_str = NULL;
	i = 0;
	while (str[++i])
	{
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

static int   variable_to_string(char *str, int i, t_list **list, t_arguments *args)
{
	char	*value;
    char	*fragment;
    
	value = NULL;
    fragment = NULL;
    fragment = get_variable_onstring(&str[i]);
	value = get_env_var(args->envp, fragment);
    ft_lstadd_back(list, ft_lstnew(value));
    i = advance_to_next_variable(str, i);
	free(fragment);
    return (i);
}

/** PURPOSE : Takes a string, expands $VARIABLES by loading
 * a linked list and then joiniing each node to create a single string result. */
char	*ultra_expansion(char *str, t_arguments *args)
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
		if (str[i] == SINGLE)
		{
			i = advance_to_next_quote(str, i);
			fix_previous_line(str, t, i, &list);
		}
		else if (str[i] == EXPAN)
		{
            i = variable_to_string(str, i, &list, args);
		}
		else
		{
			while (str[i] && str[i] != EXPAN && str[i] != SINGLE)
				i++;
			fix_previous_line(str, t, i, &list);
            printf("%i\n", i);
		}
		t = i;
	}
	new_str = build_from_list(list);
	ft_fullclear(list);
	return (new_str);
}