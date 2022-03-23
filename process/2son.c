/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/23 12:16:00 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes first forked proccess. The only thing
 * that it takes into account is if input comes from file. */
int	first_son(t_arguments *args)
{
	int			fd_write;
	t_command	*command_struct;
	int			ret;

	set_signal(1);
	command_struct = NULL;
	command_struct = get_command_struct(args, command_struct);
	ret = get_builtins_ret(args, command_struct);
	fd_write = prepare_process(args->fds[0], args->fds[1]);
	if (dup2(fd_write, STDOUT_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(fd_write);
	if (ret >= 0 && !command_struct->heredoc_file)
	{
		write_pipe_to(args->wpipe, &ret);
		free_heap_memory(args);
		exit(0);
	}
	ret = (do_execve(args, command_struct));
	write_pipe_to(args->wpipe, &ret);
	exit(0);
}

/** PURPOSE : Executes first forked proccess. The only thing
 * that it takes into account is if output comes from file. */
int	last_son(int index, t_arguments *args)
{	
	t_command	*command_struct;
	int			ret;

	set_signal(1);
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct || !command_struct->command)
		ft_shutdown(LST, 0, args);
	ret = get_builtins_ret(args, command_struct);
	if (dup2(args->fds[index], STDIN_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(args->fds[index]);
	command_file_setup(command_struct, args);
	if (ret >= 0)
		return (ret);
	return (do_execve(args, command_struct));
}
