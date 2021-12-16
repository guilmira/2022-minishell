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

/** an array of function pointers (that takes 
 * two arrays of strings and return an int) */
static int	(*builtin_func[])(char **, t_arguments *) = {
		&msh_echo,
		&msh_cd,
		&msh_pwd,
		&msh_export,
		&msh_unset,
		&msh_env,
		&msh_exit,
		&msh_help
};

int
	msh_num_builtins(void)
{
	return (sizeof(g_builtin_str) / sizeof(char *));
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

/** PURPOSE : Main execution function.
 * 1. Checks that arguments exists. 
 * 2. Checks if a built-in argument was introduced.
 * 3. Executes commands and takes program to the FORKS section. */
int	msh_execute(char **args, t_arguments *arguments)
{
	int	i;
	int	status;

	if (args[0] == NULL || !arguments)
		return (1);
	i = 0;
	while (i < msh_num_builtins())
	{	
		if (ft_strcmp(args[0], g_builtin_str[i]) == 0)
			return ((*builtin_func[i])(args, arguments));
		i++;
	}
	status = process_excution(arguments);
	return (status);
}