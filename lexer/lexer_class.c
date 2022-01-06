/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_class.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:54:39 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/06 15:12:44 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Counts positions on a table .*/
int	count_table(char **table)
{
	int i;

	if (!table)
		return (0);
	i = -1;
	while (table[++i])
		;
	return (i);
}

/** PURPOSE : Assigns a number for each token.
 * 0	PIPE
 * 1	REDIRECT
 * 2	FILE
 * 5	COMMAND TOKEN . */
int	*class_lex_table(char **lexer_table)
{
	int i;
	int	*type;
	int total_types;

	total_types = count_table(lexer_table);
	if (!total_types)
		return (NULL);
	type = ft_calloc(total_types, sizeof(int));
	if (!type)
		return (NULL);
	i = -1;
	while (lexer_table[++i])
	{
		if (!ft_strcmp(lexer_table[i], PIPE))
			type[i] = 0;
		else if (is_lex_symbol(lexer_table[i]))
			type[i] = 1;
		else if (i != 0 && type[i - 1] == 1)
			type[i] = 2;
		else
			type[i] = 5;
	}
	return (type);
}