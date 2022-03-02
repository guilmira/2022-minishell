/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0dollar_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:21:40 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/02 11:16:03 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	necessary_expansion(char first, char second)
{
    if (first == EXPAN)
        if (second != SINGLE && second != DOUBLE)
            return (1);
    return (0);
}

char	*ultra_expansion(char *str, t_arguments *args)
{
	int		i;
	int		t;
	char	*new_str;
	//t_list	*list;

	//list = NULL;
	new_str = NULL;
	i = 0;
	t = 0;
	while (str[i])
	{
		if (str[i] == SINGLE)
			i = advance_to_next_quote(str, i);
		else if (str[i] == EXPAN)
			args = (void *) args;//SUTITUIR
		else
		{
			while (str[i] && str[i] != EXPAN)
				i++;
			/* fix_previous_line(str, t, i, &list);
			t = i; */
		}
		t = i;
	}
	//new_str = build_line_form_list(list);
	//ft_fullclear(list);
	return (new_str);
}


static int	needs_expansion(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		printf("aqui\n");
		if (!ft_strchr(&str[i], EXPAN))
			return (0);
		if (str[i] == SINGLE)
		{
			
			i = advance_to_next_quote(str, i);
			printf("%i\n", i);
			if (!str[i])
				break;
		}
		else if (str[i] == EXPAN && str[i + 1])
		{
			if (str[i + 1] != SINGLE && str[i + 1] != DOUBLE && str[i + 1] != EXPAN)
				return (1);
			i++;
		}
		else
			i++;
		
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