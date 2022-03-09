/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1linked_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:18:52 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 15:10:52 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
void	arg_reader(char **table, t_arguments *args)
{
	args->total_commands = count_pipes(table) + 1;
	args->commands_lst = load_linked_list(table, args->envp, \
	args->total_commands, args);
	if (!args->commands_lst)
		ft_shutdown(ARG, 0, args);
}
