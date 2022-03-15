/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:47:01 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/15 13:11:14 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: returns the number of builtin commands.
*/
int
	msh_num_builtins(t_arguments *arg)
{
	return ((int)get_arr_len(arg->prog->builtin_str));
}

/** PURPOSE : Executes indetrmined number of processes.
 * 1. Executes single process if that is the case.
 * 2. Create argument descriptors to link pipes. 
 * 3. Accesses main process function. */
static int
	process_execution(t_arguments *arguments)
{
	t_command	*command_table;

	command_table = arguments->commands_lst->content;
	if (arguments->total_commands > MAX_COMMANDS)
	{
		printf("Input commands must be less than %i.\n", MAX_COMMANDS);
		return (1);
	}
	if (arguments->total_commands == 1)
		return (single_process(arguments));
	if (!ft_strcmp("top", command_table->command[0]))
	{
		printf(ONLYTOP);
		return (single_process(arguments));
	}
	arguments->fds = arg_descriptors(arguments);
	process_exe(arguments);
	return (1);
}

/** PURPOSE : Main execution function.
 * 1. Checks that arguments exists. 
 * 2. Checks if a built-in argument was introduced.
 * 3. Executes commands and takes program to the FORKS section. */
int
	msh_execute(char **args, t_arguments *arguments)
{
	if (args[0] == NULL || !arguments || !arguments->commands_lst)
		return (1);
	return (process_execution(arguments));
}
