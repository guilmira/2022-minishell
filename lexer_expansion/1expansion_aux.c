/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1expansion_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 10:15:06 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/03 13:11:33 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Builds a single string from all nodes. */
char	*build_from_list(t_list *list)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	str = ft_strdup(list->content);
	if (!str)
		return (NULL);
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
	{
		if (line[i] == RIDDLER || !ft_isalnum(line[i]) || ft_isspaces(line[i]))
			break;

	}
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
		if (str[i] == RIDDLER || ft_isspaces(str[i]) || !ft_isalnum(str[i]))
		{
			new_str = ft_substr(str, 1, i - 1);
			break;
		}
		else if (!str[i + 1])
			new_str = ft_substr(str, 1, i);
	}
	return (new_str);
}

/** PURPOSE : Turn value of variable into a string and adds it to a linked list. */
static int   variable_to_string(char *str, int i, t_list **list, t_arguments *args)
{
	char	*value;
    char	*fragment;
    
	value = NULL;
    fragment = NULL;
	if (str[i + 1] == RIDDLER)
	{
		value = ft_itoa(args->status);
		i = i + 2;
	}
	else
	{
    	fragment = get_variable_onstring(&str[i]);
		value = get_env_var(args->envp, fragment);
		if (!fragment)
			ft_shutdown("Failure on env variable\n", 1, args);
		if (!value) 
		value = get_env_var(args->lenvp, fragment);
		if (!value)
			value = ft_strdup(" "); 
		printf("value obtained(either local or global is): %s\n", value);
		free(fragment);
    	i = advance_to_next_variable(str, i);
	}
    ft_lstadd_back(list, ft_lstnew(value));
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
		if (!str[i])
			break;
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
		}
		t = i;

	}
	
	new_str = build_from_list(list);
	ft_fullclear(list);
	return (new_str);
}