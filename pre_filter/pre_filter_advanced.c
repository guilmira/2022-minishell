/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter_advanced.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:15:17 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/17 12:19:11 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO, : thing like [echo "hola ' "] must work and its not working at the moment

/** PURPOSE : Chech for arguments such as > " " */
static int	hanging_quotes(char *line)
{
	int		i;
	int		flag;
	char	**table;

	table = ft_split(line, ' ');
	flag = 0;
	i = -1;
	while (table[++i])
		if (!ft_strcmp(table[i], "\"") || !ft_strcmp(table[i], "\'"))
			flag++;
	ft_free_split(table);
	if (flag)
		return (1);
	else
		return (0);
}

/** PURPOSE : SECOND filter of command line.
 * Related to proper use of quotes. */
int	pre_filter_advanced(char *line)
{
	if (quotes_filter(line))
	{
		printf("Quotes (\" or '') must be closed\n");
		return (1);
	}
	if (hanging_quotes(line))
	{
		printf("Incorrect quoting use.\n");
		printf("Please make sure quotes are not empty when entering commands\n");
		return (1);
	}
	return (0);
}
