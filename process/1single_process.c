/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/16 09:34:56 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes a one only forked proccess. */
static void	single_son(t_arguments *args)
{
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shutdown(LST, 0, args);
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shutdown(EXE_ERROR, 0, args);
}

/** PURPOSE : Executes fork function for a single command. */
void	single_process(t_arguments *args)
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
