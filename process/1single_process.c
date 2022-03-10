/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/10 17:10:22 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes fork function for a single command. */
int
	single_process(t_arguments *args)
{
	int			i;
	int			status;
	int			identifier;
	t_command	*command_struct;
	int			pipe_status;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct->command)
		return (0);
	i = -1;
	while (++i < msh_num_builtins(args))
		if (!ft_strcmp(args->prog->builtin_str[i], command_struct->command[0]))
			return ((args->builtin_func[i])(command_struct->command, args));
	if (export_new_l_variables(command_struct->command, args))
		return (1);
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
		i = single_son(args);
		write_child_status(args, &i);
		exit(0);
	}
	else if (identifier > 0)
	{
		wait(&status);
		read_child_status(args);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (1);
}
