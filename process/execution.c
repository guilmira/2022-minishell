/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:09:13 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/11 14:28:44 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	fork_end_son(t_arguments *args, int last_index)
{
	int	identifier;
	int	i;
	int	wstatus;

	identifier = fork();
	if (identifier == 0)
	{
		i = last_son(last_index, args);
		write_pipe_to(args->wpipe, &i);
		exit(0);
	}
	else if (identifier > 0)
	{
		read_pipe_from(args->wpipe, &args->status);
		wait(&wstatus);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
}

/** PURPOSE : End of the process.
 * 1. Final fork + execute last son. */
static int	end_process(t_arguments *args)
{
	int	last_index;

	args->command_number++;
	last_index = (args->command_number * 2) - 2;
	set_status(args, 0);
	if (pipe(args->wpipe) == -1)
	{
		perror("PIPE ERROR\n");
		set_status(args, 1);
		return (1);
	}
	fork_end_son(args, last_index);
	return (1);
}

/** PURPOSE : Executes fork function to run commands.
 * 1. Create first pipe. 
 * 2. Fork process in a loop, and inside each son process, run command.
 * 3. Continue running program until last fork. */
int	process_exe(t_arguments *args)
{
	int	i;
	int	wstatus;
	int	identifier;
	int	x;

	if (pipe(args->fds) == -1)
		ft_shutdown(MSG, 0, args);
	if (pipe(args->wpipe) == -1)
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
		read_pipe_from(args->wpipe, &args->status);
		i = -1;
		close(args->fds[1]);
		while (++i < args->total_commands - 2)
		{
			x = mid_process(args);
			if (x < 0)
			{
				set_status(args, 1);
				ft_shutdown(EXE_ERROR, 0, args);
			}
			else if (x == 0)
				return (0);
		}
		x = end_process(args);
		/* int t = -1;
		while (++t < 2)
		{
			printf("ese: %i\n", t);
			wait(&wstatus);
		} */
		wait(&wstatus);
		if (x < 0)
		{
			set_status(args, 1);
			ft_shutdown(EXE_ERROR, 0, args);
		}
		//waiting_process(&status);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (1);
}
