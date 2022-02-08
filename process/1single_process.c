/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/04 12:09:38 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes fork function for a single command. */
int
	single_process(t_arguments *args)
{
	int			status;
	int			identifier;
	t_command	*command_struct;
	char		**cmdwargs;
	int			i;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	cmdwargs = command_struct->command;
	if (!cmdwargs)
		return (0); //error, no command
	i = 0;
	while (i < msh_num_builtins(args))
	{
		if (ft_strcmp(cmdwargs[0], args->prog->builtin_str[i]) == 0)
			return ((args->builtin_func[i])(cmdwargs, args));
		i++;
	}
	g_rv = 1;
	identifier = fork();
	if (identifier == 0)
	{
		g_rv = single_son(args);
		exit (0);
	}
	else if (identifier > 0)
		wait(&status);
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (g_rv); //to make function work
}
