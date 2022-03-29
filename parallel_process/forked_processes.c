/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:08:19 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/26 23:08:20 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	manage_pipes(t_command *cmd, t_command *prev_cmd,
		int index, t_arguments *args)
{
	int	last_index;

	last_index = args->total_commands - 1;
	if (index != last_index && !cmd->list_delimeters)
	{
		close(cmd->pipes[READ_FD]);
		if (dup2(cmd->pipes[WRITE_FD], STDOUT_FILENO) == -1)
			ft_shutdown(DUP_ERROR, 0, args);
		close(cmd->pipes[WRITE_FD]);
	}
	if (index != 0)
	{
		if (dup2(prev_cmd->pipes[READ_FD], STDIN_FILENO) == -1)
			ft_shutdown(DUP_ERROR, 0, args);
		close(prev_cmd->pipes[READ_FD]);
	}
}

int
	child_process_routine(t_command *cmd, t_command *prev_cmd,
		int index, t_arguments *args)
{
	int	ret;

	ret = 1;
	manage_pipes(cmd, prev_cmd, index, args);
	if (is_builtin(cmd, args))
		ret = get_builtins_ret(args, cmd);
	else
		ret = (do_execve(args, cmd));
	return (ret);
}
