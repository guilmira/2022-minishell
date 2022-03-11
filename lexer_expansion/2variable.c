/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2variable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:48:27 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/11 12:27:36 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Advance to INMIDATE next piece of variable. */
static int	advance_to_next_variable(char *line, int i)
{
	if (!line)
		return (i);
	while (line[++i])
		if (line[i] == RIDDLER || !ft_isalnum(line[i]) || ft_isspaces(line[i]))
			break ;
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
			break ;
		}
		else if (!str[i + 1])
			new_str = ft_substr(str, 1, i);
	}
	return (new_str);
}

/** PURPOSE : Normi impossed. */
static char	*get_value_variable(char *fragment, t_arguments *args)
{
	char	*value;

	if (!fragment)
		ft_shutdown("Failure on env variable\n", 1, args);
	value = get_env_var(args->envp, fragment, false);
	if (!value)
		value = get_env_var(args->lenvp, fragment, false);
	if (!value)
		value = ft_strdup(""); //CUIDADO AQUI PUEDE HABER SEGFAULTS Y LEAKS
	free(fragment);
	return (value);
}

/** PURPOSE : Turn value of variable into a string 
 * and adds it to a linked list. */
int	variable_to_string(char *str, int i, \
t_list **list, t_arguments *args)
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
		value = get_value_variable(fragment, args);
		i = advance_to_next_variable(str, i);
	}
	ft_lstadd_back(list, ft_lstnew(value));
	return (i);
}
