/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0dollar_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:21:40 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/01 12:18:52 by guilmira         ###   ########.fr       */
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

char	*get_fragment(char *str, int i)
{
	int j;
	char *new_str;

	new_str = NULL;
	j = i;
	while (str[++j])
	{
		if (!str[j + 1])
			new_str = ft_substr(str, i + 1, j - i);
		else if (str[j] == ' ' || str[j] == EXPAN || str[j] == SINGLE)
		{
			new_str = ft_substr(str, i + 1, j - i - 1);
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
	//t_list	*list;

	char	*tail;

	tail = NULL;
	//list = NULL;

	new_str = NULL;
	i = 0;
	t = 0;
	int j;
	char *fragment = NULL;
	char *value = NULL;
	j = -1;
	while (str[i])
	{
		if (str[i] == SINGLE)
			i = advance_to_next_quote(str, i);
		else if (str[i] == EXPAN)
		{
			fragment = get_fragment(str, i);
			printf("fragment %s\n", fragment);
			i++;
			value = get_env_var(args->envp, fragment);
			printf("value: %s\n", value);
			ft_strlen(fragment);
			printf("HERE IS THE OUTPUT\n");
			printf("%s", ft_substr(str, 0, i -1));
			printf("%s", value);
			printf("%s\n", ft_substr(str, i + 1, ft_strlen(str) - 1)); //+ ft_strlen(str)
			//substitute(str, fragment, value);
			/*while (args->envp[++j])
			{
				if (args->envp[j][0] == 'a')
					tail = ft_strdup(ft_strchr(args->envp[j], '='));
				printf("%s\n", tail);
			}
			new_str = tail++;
			
			printf("imprime: %s\n", new_str);
			i++; */
		}
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
			//printf("NECESTA EXPANDIR\n");
			//args = (void *) args;
			new_str = ultra_expansion(str, args);
			free(str);
			table[i] = new_str;
		}
	}
	return (table);
}