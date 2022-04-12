/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 06:42:52 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/27 12:58:02 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Creates required number of parallel son. */
static int
	create_son(t_command *cmd, t_command *prev_cmd,
		int index, t_arguments *args)
{
	int			last_index;
	pid_t		pid;
	int			ret;

	init_local_variables(args, &last_index, &ret);
	pid = fork();
	if (pid == 0)
	{
		ret = child_process_routine(cmd, prev_cmd, index, args);
		exit(ret);
	}
	else if (pid > 0)
	{
		cmd->pid = pid;
		close_p_pipes(cmd, prev_cmd, index, last_index);
		return (ret);
	}
	else
		set_status_and_shut(args, FORK_ERROR);
	return (pid);
}

void
	initialize_variables(int *ret, int *index, t_command **prev_cmd)
{
	(*prev_cmd) = NULL;
	(*index) = -1;
	(*ret) = 0;
}

int
	get_ret(t_arguments *args, const t_command *cmd, pid_t waited_pid)
{
	int	ret;
	int	st;

	ret = 1;
	if (waited_pid != -1)
	{
		if (WIFEXITED(cmd->control))
		{
			st = WEXITSTATUS(cmd->control);
			if (st >= 0 && st <= 1)
				set_status(args, 0);
			if (st == 232)
				ret = 0;
		}
		else if (WIFSIGNALED(cmd->control))
			set_status(args, 130);
		else if (WIFSTOPPED(cmd->control))
			set_status(args, 127);
		else
			set_status(args, 1);
	}
	return (ret);
}

/** PURPOSE : Executes fork function to run commands.
 * 1. Create first pipe.
 * 2. Fork process in a loop, and inside each son process, run command.
 * 3. Continue running program until last fork. */
int
	processing(t_arguments *args)
{
	int			ret;
	int			index;
	t_command	*cmd;
	t_command	*prev_cmd;
	pid_t		waited_pid;

	initialize_variables(&ret, &index, &prev_cmd);
	while (++index < args->total_commands)
	{
		cmd = get_cmd(args, index);
		if (index != 0)
			prev_cmd = get_cmd(args, index - 1);
		create_pipe(cmd, index, args);
		ret = create_son(cmd, prev_cmd, index, args);
	}
	index = -1;
	while (++index < args->total_commands)
	{
		cmd = get_cmd(args, index);
		waited_pid = waitpid(cmd->pid, &(cmd->control), 0);
		ret = get_ret(args, cmd, waited_pid);
	}
	return (ret);
}
