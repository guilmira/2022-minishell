/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2linked_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:22:08 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/14 14:44:30 by asydykna         ###   ########.fr       */
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

/** PURPOSE : Allocate space for table by counting words. */
static char	**alloc_table(int i, char **table, t_arguments *args)
{
	int		words;
	char	**command_table;

	words = count_command_words(table, i);
	if (!words)
		ft_shutdown(MEM, 2, args);
	command_table = ft_calloc((count_command_words(table, i) + 1), \
	sizeof(char *));
	if (!command_table)
		ft_shutdown(MEM, 2, args);
	return (command_table);
}

/** PURPOSE : Normi impossed. */
void	set_table(t_command *command_struct, \
char **command_table, t_arguments *args)
{
	if (!command_table[0])
		command_table[0] = ft_strdup(BLANK);
	if (!command_table[0])
		ft_shutdown(MEM, 2, args);
	command_struct->command = command_table;
}

/** PURPOSE : Converter. Skips lex_PIPE, lex_symbols and file names
 * If there is nothing to get, it yields lex_BLANK. */
void	load_command_struct(t_command *command_struct, char **table, \
int i, t_arguments *args)
{
	int		j;
	char	**command_table;

	i = obtain_position(table, i);
	command_table = alloc_table(i, table, args);
	j = 0;
	i = i - 1;
	while (table[++i])
	{
		if (!ft_strcmp(PIPE, table[i]))
			break ;
		if (!ft_strcmp(IN, table[i]) || !ft_strcmp(OUT, table[i]) \
		|| !ft_strcmp(APPEND, table[i]))
			i++;
		else
		{
			command_table[j] = ft_strdup(table[i]);
			if (!command_table[j])
				ft_shutdown(MEM, 2, args);
			j++;
		}
	}
	free(command_table[j]);
	command_table[j] = NULL;
	set_table(command_struct, command_table, args);
}
