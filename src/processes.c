/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:47:01 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/09 15:07:24 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//an array of function pointers (that takes two arrays of strings and return an int)
static int	(*builtin_func[])(char **, t_data *) = {
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


/** PURPOSE : Executes indtermined number of processes.
 * 1. Create argument descriptors to link pipes. 
 * 2. Accesses main process function. */
static int	process_excution(t_arguments *arguments)
{
	arguments->fds = arg_descriptors(arguments);
	process_exe(arguments);
	return (1);
}

int	msh_execute(char **args, t_data *data, t_arguments *arguments)
{
	int	i;
	int	status;

	
	if (args[0] == NULL) //empty command was entered
		return (1);
	i = 0;
	while (i < msh_num_builtins())
	{
		if (ft_strcmp(args[0], "prueba") == 0)
		//if (ft_strcmp(args[0], g_builtin_str[i]) == 0) //TODO da seg fault. Comprobar.
			return ((*builtin_func[i])(args, data));
		i++;
	}
	status = process_excution(arguments);
	return (status);
}
