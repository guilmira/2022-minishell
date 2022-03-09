/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0dollar_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:21:40 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 15:03:43 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Evaluates whether there is a $ that is not locate
 * between single quotes ('$USER', this should not expand.) */
int	needs_expansion(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_strchr(&str[i], EXPAN))
			return (0);
		if (str[i] == SINGLE)
		{
			i = advance_to_next_quote(str, i);
			if (!str[i])
				break ;
			i = i - 1;
		}
		else if (str[i] == EXPAN && str[i + 1])
		{
			if (str[i + 1] == RIDDLER || ft_isalnum(str[i + 1]))
				return (1);
		}
	}
	return (0);
}

/** PURPOSE : Takes a table of strings and expands variables.
 * This is finding the $ symbol, tkaen the variable ad substitute
 * said variable for its value. Some examples: 
 * export alfa=l   export beta=s  COMMAND  $alfa$beta
 * 	--> 	table[0] = ls (output result, ls) */
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

/** PURPOSE : Tokens in existence. */
void	init_options(char **option, char **option_name)
{
	option[0] = "|";
	option_name[0] = PIPE;
	option[1] = "<";
	option_name[1] = IN;
	option[2] = ">";
	option_name[2] = OUT;
	option[3] = ">>";
	option_name[3] = APPEND;
	option[4] = "<<";
	option_name[4] = HEREDOC;
	option[5] = NULL;
	option_name[5] = NULL;
}
