/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:09:13 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/08 15:50:28 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : End of the process.
 * 1. Final fork + execute last son. */
static int	end_process(t_arguments *args)
{
	int	identifier;
	int	status;
	int	last_index;
	int	i;
	int	pipe_status;

	i = 1;
	args->command_number++;
	last_index = (args->command_number * 2) - 2;
	set_status(args, 0);
	pipe_status = pipe(args->wpipe);
	if (pipe_status == -1)
	{
		perror("PIPE ERROR\n");
		set_status(args, 1);
		return (1);
	}
	identifier = fork();
	if (identifier == 0)
	{
		i = last_son(last_index, args);
		write_pipe_to(args->wpipe, &i);
		exit(0);
	}
	else if (identifier > 0)
	{
		wait(&status);
		read_pipe_from(args->wpipe, &args->status);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (i);
}

/** PURPOSE : Executes fork function to run commands.
 * 1. Create first pipe. 
 * 2. Fork process in a loop, and inside each son process, run command.
 * 3. Continue running program until last fork. */
int	process_exe(t_arguments *args)
{
	int	i;
	int	status;
	int	identifier;
	int	pipe_status;
	int	x;

	if (pipe(args->fds) == -1)
		ft_shutdown(MSG, 0, args);
	pipe_status = pipe(args->wpipe);
	if (pipe_status == -1)
	{
		perror("PIPE ERROR\n");
		set_status(args, 1);
		return (1);
	}
	identifier = fork();
	if (identifier == 0)
	{
		x = first_son(args);
		write_pipe_to(args->wpipe, &x);
		exit(0);
	}
	else if (identifier > 0)
	{
		i = -1;
		wait(&status);
		close(args->fds[1]);
		while (++i < args->total_commands - 2)
		{
			x = mid_process(args);
			read_pipe_from(args->wpipe, &args->status);
			if (x < 0)
			{
				set_status(args, 1);
				ft_shutdown(EXE_ERROR, 0, args);
			}
			else if (x == 0)
				return (0);
		}
		x = end_process(args);
		if (x < 0)
		{
			set_status(args, 1);
			ft_shutdown(EXE_ERROR, 0, args);
		}
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (1);
}
