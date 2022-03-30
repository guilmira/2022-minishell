/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:09:13 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/30 10:42:51 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	fork_end_son(t_arguments *args, int last_index)
{
	int	identifier;
	int	i;
	int	wstatus;

	if (!check_command(args))
	{
		close(args->fds[last_index]);
		close(args->fds[last_index + 1]);
		perror("minishell");
		return ;
	}
	identifier = fork();
	if (identifier == 0)
	{
		i = last_son(last_index, args);
		write_pipe_to(args->wpipe, &i);
		exit(0);
	}
	else if (identifier > 0)
		father_process_routine(args, last_index, &i, &wstatus);
	else
		ft_shutdown(FORK_ERROR, 0, args);
}

/** PURPOSE : End of the process.
 * 1. Final fork + execute last son. */
int
	end_process(t_arguments *args)
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

void
	do_end_process(t_arguments *args, int x)
{
	int	wstatus;

	x = end_process(args);
	wait(&wstatus);
	if (x < 0)
		set_status_and_shut(args, EXE_ERROR);
}

int
	fork_ret(t_arguments *args)
{
	int	i;
	int	identifier;
	int	x;

	identifier = fork();
	if (identifier == 0)
		first_son(args);
	else if (identifier > 0)
	{
		read_pipe_from(args->wpipe, &args->status);
		i = -1;
		close(args->fds[1]);
		while (++i < args->total_commands - 2)
		{
			x = mid_process(args);
			if (x < 0)
				set_status_and_shut(args, EXE_ERROR);
			else if (x == 0)
				return (0);
		}
		do_end_process(args, x);
	}
	else
		set_status_and_shut(args, FORK_ERROR);
	return (1);
}

/** PURPOSE : Executes fork function to run commands.
 * 1. Create first pipe. 
 * 2. Fork process in a loop, and inside each son process, run command.
 * 3. Continue running program until last fork. */
int
	process_exe(t_arguments *args)
{
	if (!args->heredoc_det)
	{
		processing(args);
		return (1);
	}
	if (pipe(args->fds) == -1 || pipe(args->wpipe) == -1)
		set_status_and_shut(args, MSG);
	if (!check_command(args))
	{
		close(args->fds[0]);
		close(args->fds[1]);
		return (1);
	}
	return (fork_ret(args));
}
