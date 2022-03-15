/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/15 13:11:24 by guilmira         ###   ########.fr       */
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

int
	is_executable(t_arguments *args)
{
	int			i;
	int			path_exists;
	char		**folders;
	char		*command_path;
	t_command	*cmd;

	folders = get_env_path(args->envp);
	cmd = args->commands_lst->content;
	command_path = NULL;
	i = -1;
	path_exists = 0;
	while (folders[++i] && !path_exists)
	{
		command_path = ft_strjoin(folders[i], cmd->command[0]);
		if (file_exists(command_path))
			path_exists++;
		free(command_path);
	}
	ft_free_split(folders);
	if (!path_exists)
		return (0);
	return (1);
}

bool	check_command(t_arguments *args)
{
	if (!is_executable(args))
	{
		errno = ENOENT;
		perror("minishell");
		set_status(args, 127);
		close(args->wpipe[0]);
		close(args->wpipe[1]);
		return (0);
	}
	return (1);
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
	int			save_stdout;
	int			ret;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct || !command_struct->command)
		ft_shutdown(LST, 0, args);
	save_stdout = get_stdout_copy(args, command_struct);
	ret = builtin_routine(args, command_struct, save_stdout);
	if (ret >= 0)
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
