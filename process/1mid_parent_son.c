/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1mid_parent_son.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/08 12:21:54 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//frees
void	clean_memory(t_arguments *args)
{
	if (args)
	{
		if (args)
			args = (void *)args; //todo function
	}
}

/** PURPOSE : Executes forked process for all the mid commands
 * 1. Sets truct of command. Identify its path.
 * 2. Sets the proper inputs and outputs, redirecting the
 * exits (like STDOUT_FILENO) to the correct pipe file descriptor. 
 * 3. Executes command by searching in path with execve. */
static void	mid_son(int index, t_arguments *args)
{
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shutdown(LST, 0, args);
	if (dup2(args->fds[index - 2], STDIN_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(args->fds[index - 2]);
	if (dup2(args->fds[index + 1], STDOUT_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(args->fds[index + 1]);
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shutdown(EXE_ERROR, 0, args);
}

/** PURPOSE : Mid process for all the commands that are not
 * wither the  first one or the last one.
 * 1. Establish syntax and index.
 * 2. Forks the process annd creates a single son.
 * 2. Excutes mid_son and waits for it to finish. */
void	mid_process(t_arguments *args)
{
	int	index;
	int	status;
	int	identifier;

	args->command_number++;
	index = args->command_number * 2;
	if (pipe(&args->fds[index]) == -1)
		ft_shutdown(MSG, 0, args);
	identifier = fork();
	if (identifier == 0)
	{
		close(args->fds[index]);
		mid_son(index, args);
	}
	else if (identifier > 0)
	{
		wait(&status);
		close(args->fds[index + 1]);
		return ;
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
}
