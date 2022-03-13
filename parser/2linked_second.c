/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2linked_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:22:08 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/13 08:12:46 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Count words in command in order to allocate. */
static int	count_command_words(char **table, int i)
{
	int	words;

	words = 1;
	if (!table || !table[0])
		return (0);
	while (table[++i])
	{
		if (!ft_strcmp(PIPE, table[i]))
			return (words);
		words++;
	}
	return (words);
}

/** PURPOSE : Number of command 0 is equivalent to first command. */
static int	obtain_position(char **table, int number_of_command)
{
	int	i;
	int	number_appeared;

	if (!number_of_command)
		return (0);
	i = -1;
	number_appeared = 0;
	while (table[++i])
	{
		if (!ft_strcmp(PIPE, table[i]))
			number_appeared++;
		if (number_appeared == number_of_command)
			return (i + 1);
	}
	return (i);
}

/** PURPOSE : Converter. THE ONLY THING THAT SKIPS
 * IS LEX_PIPE. THE REST, IS TREATED AS INPUT. */
void	load_command_struct(t_command *command_struct, char **table, \
int i, t_arguments *args)
{
	int		j;
	int		words;
	char	**command_table;

	i = obtain_position(table, i);
	words = count_command_words(table, i);
	if (!words)
		ft_shutdown(MEM, 2, args);
	command_table = ft_calloc((count_command_words(table, i) + 1), \
	sizeof(char *));
	if (!command_table)
		ft_shutdown(MEM, 2, args);
	j = 0;
	i = i - 1;
	while (table[++i])
	{
		if (!ft_strcmp(PIPE, table[i]))
			break ;
		command_table[j] = ft_strdup(table[i]);
		if (!command_table[j])
			ft_shutdown(MEM, 2, args);
		j++;
	}
	command_table[j] = NULL;
	command_struct->command = command_table;
}
