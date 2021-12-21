/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:47:01 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/16 09:32:13 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	msh_num_builtins(t_arguments *arg)
{
	return ((int)get_arr_len(arg->builtin_str));
}

/** PURPOSE : Executes indetrmined number of processes.
 * 1. Executes single process if that is the case.
 * 2. Create argument descriptors to link pipes. 
 * 3. Accesses main process function. */
static int	process_excution(t_arguments *arguments)
{
	if (arguments->total_commands == 1)
	{
		single_process(arguments);
		return (1);
	}
	arguments->fds = arg_descriptors(arguments);
	process_exe(arguments);
	return (1);
}

/** PURPOSE : Show menue. Does not need to be interactive */
static void	history_printer(HIST_ENTRY **hst_entry, int provisional)
{
	int	i;

	i = -1;
	while (++i < provisional)
	{

		printf("%s\n", hst_entry[i]->line);
	}
}

//pendeinte, mover el recap del history a la lectura de la linea.
//añadir numero de orden.

/** PURPOSE : The history command.
 * In development, I ll take care of this part. */
static void	history_management(t_arguments *args)
{
	HISTORY_STATE	*hst_state;
	t_command		*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	//0. Build history with every command. Then load into struct.
	//1. Locate history
	hst_state = history_get_history_state();
	history_set_history_state (hst_state);
	add_history(command_struct->command[0]);
	//3. Print history, order, string and timestamp.
	
	
}


/** PURPOSE : Main execution function.
 * 1. Checks that arguments exists. 
 * 2. Checks if a built-in argument was introduced.
 * 3. Executes commands and takes program to the FORKS section. */
int	msh_execute(char **args, t_arguments *arguments)
{
	int	i;
	int	status;
	HIST_ENTRY		**hst_entry;
	static int provisional;

	if (args[0] == NULL || !arguments)
		return (1);
	history_management(arguments);
	provisional++;
	if (ft_strcmp(args[0], "history") == 0)
	{
		hst_entry = history_list();
		history_printer(hst_entry, provisional);
		status = 1;
		return (status);
	}
	i = 0;
	while (i < msh_num_builtins(arguments))
	{	
		if (ft_strcmp(args[0], arguments->builtin_str[i]) == 0)
			return ((arguments->builtin_func[i])(args, arguments));
		i++;
	}
	status = process_excution(arguments);
	return (status);
}
