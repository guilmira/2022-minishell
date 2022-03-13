/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1linked_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:18:52 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/13 10:18:44 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Number of command 0 is equivalent to first command. */
int	obtain_position(char **table, int number_of_command)
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

/** PURPOSE : Count total number of pipes. */
static int	count_pipes(char **lexer_table)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (lexer_table[++i])
		if (!ft_strcmp(PIPE, lexer_table[i]))
			j++;
	return (j);
}

/** PURPOSE : Load arguments into structure. 
 * 1. Allocates memory for structure.
 * 2. Creates linked list to manage any number of commands */
void	arg_reader(char **table, int*lexer_type, t_arguments *args)
{
	args->total_commands = count_pipes(table) + 1;
	args->commands_lst = load_linked_list(table, lexer_type, args->envp, args);
	if (!args->commands_lst)
		ft_shutdown(ARG, 0, args);
}
