/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_process_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:45:23 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/26 19:45:24 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Creates a pipe, except in the case where the last
 * command of the command line is being executed. */
void
	create_pipe(t_command *cmd, int index, t_arguments *args)
{
	int	last_command_index;

	last_command_index = args->total_commands - 1;
	if (index != last_command_index)
		if (pipe(cmd->pipes) == -1)
			set_status_and_shut(args, MSG);
}

void
	make_pipe(t_arguments *args, int *wpipe)
{
	if (pipe(wpipe) == -1)
		set_status_and_shut(args, MSG); //ft_shudown is absent. check it before deleting the comment
}

void
	close_p_pipes(const t_command *cmd, const t_command *prev_cmd,
		int index, int last_index)
{
	if (index != last_index)
		close(cmd->pipes[WRITE_FD]);
	if (index != 0)
		close(prev_cmd->pipes[READ_FD]);
}

void
	init_local_variables(t_arguments *args, int *last_index, int *ret)
{
	set_status(args, 0);
	(*last_index) = args->total_commands - 1;
	(*ret) = 1;
}

void
	change_current_directory(t_arguments *args)
{
	char		*new_pwd;

	new_pwd = get_env_var(args->envp, "PWD", false);
	chdir(new_pwd);
	free(new_pwd);
}
