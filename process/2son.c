/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/13 14:27:45 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes first forked proccess. The only thing
 * that it takes into account is if input comes from file. */
int
	first_son(t_arguments *args)
{
	int			i;
	int			fd_write;
	t_command	*command_struct;

	set_signal(1);
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct || !command_struct->command)
		ft_shutdown(LST, 0, args);
	fd_write = prepare_process(args->fds[0], args->fds[1]);
	//manage_input_redirection(args);
	if (dup2(fd_write, STDOUT_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(fd_write);
	set_status(args, 0);
	i = 0;
	while (i < msh_num_builtins(args))
	{
		if (!ft_strcmp(args->prog->builtin_str[i], command_struct->command[0]))
			return ((args->builtin_func[i])(command_struct->command, args));
		i++;
	}
	if (args->heredoc_list)
		return (heredoc_routine(args->heredoc_list));
	if (export_new_l_variables(command_struct->command, args))
		return (1);
	return (do_execve(args, command_struct));
}

/** PURPOSE : Executes first forked proccess. The only thing
 * that it takes into account is if output comes from file. */
int
	last_son(int index, t_arguments *args)
{	
	t_command	*command_struct;
	int			i;

	set_signal(1);
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct || !command_struct->command)
		ft_shutdown(LST, 0, args);
	if (dup2(args->fds[index], STDIN_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(args->fds[index]);
	command_file_setup(command_struct, args);
	set_status(args, 0);
	i = 0;
	while (i < msh_num_builtins(args))
	{
		if (!ft_strcmp(args->prog->builtin_str[i], command_struct->command[0]))
			return ((args->builtin_func[i])(command_struct->command, args));
		i++;
	}
	if (args->heredoc_list)
		return (heredoc_routine(args->heredoc_list));
	if (export_new_l_variables(command_struct->command, args))
		return (1);
	return (do_execve(args, command_struct));
}
