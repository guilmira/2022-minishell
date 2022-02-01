/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:47:01 by asydykna          #+#    #+#             */
/*   Updated: 2022/01/05 15:14:41 by guilmira         ###   ########.fr       */
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
	process_excution(t_arguments *arguments)
{
	if (arguments->total_commands == 1) //this if need inside to check whether its built in or not. THis is the simplest case
	{
		single_process(arguments);
		return (1);
	}
	arguments->fds = arg_descriptors(arguments);
	process_exe(arguments);
	return (1); //status, 0 o 1
}

/** PURPOSE : Main execution function.
 * 1. Checks that arguments exists. 
 * 2. Checks if a built-in argument was introduced.
 * 3. Executes commands and takes program to the FORKS section. */
int
	msh_execute(char **args, t_arguments *arguments)
{
	int			i;
	int			status;
	t_list		*cmd_list;
	char		**new_args;

	if (args[0] == NULL || !arguments || !arguments->commands_lst)
		return (1);
	cmd_list = arguments->commands_lst;
	while (cmd_list)
	{
		if (cmd_list->content && ((t_command *)cmd_list->content)->command)
			new_args = ((t_command *)cmd_list->content)->command;
		else
			break ;
		i = 0;
		while (i < msh_num_builtins(arguments))
		{
			if (ft_strcmp(new_args[0], arguments->prog->builtin_str[i]) == 0)
				return ((arguments->builtin_func[i])(new_args, arguments));
			i++;
		}
		cmd_list = cmd_list->next;
	}
	status = process_excution(arguments);
	return (status);
}
