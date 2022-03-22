/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/22 10:19:34 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_blank(int i, t_arguments *args)
{
	t_list		*list;
	t_command	*command_struct;

	list = NULL;
	command_struct = NULL;
	list = args->commands_lst;
	while (list)
	{
		command_struct = list->content;
		if (command_struct->index == i)
			break ;
		list = list->next;
	}
	if (!ft_strcmp(BLANK, command_struct->command[0]))
		return (1);
	return (0);
}

void
	fork_single_child(t_arguments *args)
{
	int	identifier;
	int	i;
	int	wstatus;

	if (!check_command(args))
		return ;
	identifier = fork();
	if ((identifier) == 0)
	{
		i = single_son(args);
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

/** PURPOSE : Executes fork function for a single command. */
int
	single_process(t_arguments *args)
{
	t_command	*command_struct;
	int			ret;
	command_struct = NULL;
	command_struct = get_command_struct(args, command_struct);
	ret = get_builtins_ret(args, command_struct);
	if (ret >= 0 && !command_struct->heredoc_file)
		return (ret);
	if (pipe(args->wpipe) == -1)
	{
		perror("PIPE ERROR\n");
		set_status(args, 1);
		return (1);
	}

	fork_single_child(args);
	return (1);
}
