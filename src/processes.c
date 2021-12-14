/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:47:01 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 11:12:39 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//an array of function pointers (that takes two arrays of strings and return an int)
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

/** PURPOSE : Executes a one only forked proccess. */
void	single_son(t_arguments *args)
{
	t_command	*command_struct;

	
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shutdown(LST, 0, args);
	/* if (args->flag_file)
		input_form_file(args->file_input); */
	/* if (dup2(fd_write, STDOUT_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(fd_write); */
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shutdown(EXE_ERROR, 0, args);
}

/** PURPOSE : Executes fork function for a single command. */
static void	single_process(t_arguments *args)
{
	int	status;
	int	identifier;

	identifier = fork();
	if (identifier == 0)
		single_son(args);
	else if (identifier > 0)
		wait(&status);
	else
		ft_shutdown(FORK_ERROR, 0, args);
}

/** PURPOSE : Executes indtermined number of processes.
 * 1. Create argument descriptors to link pipes. 
 * 2. Accesses main process function. */
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
