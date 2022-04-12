/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1mid_parent_son.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/30 10:39:53 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void
	mnge_dups(int index, t_arguments *args, const t_command *command_struct)
{
	if (!command_struct || !command_struct->command)
		ft_shutdown(LST, 0, args);
	if (dup2(args->fds[index - 2], STDIN_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(args->fds[index - 2]);
	if (dup2(args->fds[index + 1], STDOUT_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(args->fds[index + 1]);
}

t_command
	*get_command_struct(t_arguments *args, t_command *command_struct)
{
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct || !command_struct->command)
		ft_shutdown(LST, 0, args);
	return (command_struct);
}

/** PURPOSE : Executes forked process for all the mid commands
 * 1. Sets truct of command. Identify its path.
 * 2. Sets the proper inputs and outputs, redirecting the
 * exits (like STDOUT_FILENO) to the correct pipe file descriptor. 
 * 3. Executes command by searching in path with execve. */
static int
	mid_son(int index, t_arguments *args)
{
	t_command	*command_struct;
	int			ret;

	set_signal(1);
	command_struct = NULL;
	command_struct = get_command_struct(args, command_struct);
	ret = get_builtins_ret(args, command_struct);
	if (ret >= 0 && !command_struct->heredoc_result)
		return (ret);
	mnge_dups(index, args, command_struct);
	return (do_execve(args, command_struct));
}

void
	fork_mid_child(t_arguments *args, int index)
{
	int	i;
	int	wstatus;
	int	identifier;

	if (!check_command(args))
		return ;
	identifier = fork();
	if (identifier == 0)
	{
		close(args->fds[index]);
		i = mid_son(index, args);
		write_pipe_to(args->wpipe, &i);
		exit(0);
	}
	else if (identifier > 0)
	{
		close(args->fds[index - 2]);
		read_pipe_from(args->wpipe, &i);
		wait(&wstatus);
		mnge_status(args, i);
		close(args->fds[index + 1]);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
}

/** PURPOSE : Mid process for all the commands that are not
 * wither the  first one or the last one.
 * 1. Establish syntax and index.
 * 2. Forks the process annd creates a single son.
 * 2. Excutes mid_son and waits for it to finish. */
int
	mid_process(t_arguments *args)
{
	int	index;

	args->command_number++;
	index = args->command_number * 2;
	if (pipe(&args->fds[index]) == -1)
		ft_shutdown(MSG, 0, args);
	set_status(args, 0);
	if (pipe(args->wpipe) == -1)
	{
		printf("PIPE ERROR: %s\n", strerror(errno));
		set_status(args, 1);
		return (1);
	}
	fork_mid_child(args, index);
	return (1);
}
