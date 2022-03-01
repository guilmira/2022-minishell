/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:09:13 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/01 13:41:39 by guilmira         ###   ########.fr       */
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

	args->command_number++;
	last_index = (args->command_number * 2) - 2;
	identifier = fork();
	if (identifier == 0)
	{
		g_rv = last_son(last_index, args);
		if (g_rv < 0)
			ft_shutdown(EXE_ERROR, 0, args);
		else if (g_rv == 0)
			return (0);
		else
			exit(0);
	}
	else if (identifier > 0)
		wait(&status);
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (0);
}

/** PURPOSE : Executes fork function to run commands.
 * 1. Create first pipe. 
 * 2. Fork process in a loop, and inside each son process, run command.
 * 3. Continue running program until last fork. */
int
	process_exe(t_arguments *args)
{
	int	i;
	int	status;
	int	identifier;

	if (pipe(args->fds) == -1)
		ft_shutdown(MSG, 0, args);
	g_rv = 1;
	identifier = fork();
	if (identifier == 0)
	{
		g_rv = first_son(args);
		if (g_rv < 0)
		{
			set_status(args, 1);
			ft_shutdown(EXE_ERROR, 0, args);
		}
		else if (g_rv == 0)
			return (0);
		else
			exit(0);
	}
	else if (identifier > 0)
	{
		i = -1;
		wait(&status);
		close(args->fds[1]);
		while (++i < args->total_commands - 2)
		{
			g_rv = mid_process(args);
			if (g_rv < 0)
			{
				set_status(args, 1);
				ft_shutdown(EXE_ERROR, 0, args);
			}
			else if (g_rv == 0)
				return (0);
		}
		g_rv = end_process(args);
		if (g_rv < 0)
		{
			set_status(args, 1);
			ft_shutdown(EXE_ERROR, 0, args);
		}
		else if (g_rv == 0)
			return (0);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (g_rv);
}
