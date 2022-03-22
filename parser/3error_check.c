/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3error_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:15:35 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/22 10:18:58 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Checks if binary program is executable. */
static int	is_executable(t_arguments *args)
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
		if (file_exists(command_path)) //|| !strcmp(BLANK, cmd->command[0])
			path_exists++;
		free(command_path);
	}
	ft_free_split(folders);
	if (!path_exists)
		return (0);
	return (1);
}

/** PURPOSE : Tries to open the file. */
static int	try_open(char *path)
{
	int	fd_file;

	fd_file = open(path, O_RDONLY);
	if (fd_file < 0)
		return (0);
	return (1);
}

/** PURPOSE : Checks if input does not exist. */
static int	error_input(t_arguments *args, t_command *command_struct)
{
	if (command_struct->list_in)
	{
		search_input(command_struct->list_in, args);
		if (args->file_input)
			return (!try_open(args->file_input));
	}
	return (0);
}

/** PURPOSE : Checks for error in commands.
 * 1. Whether is executable or not, by checking if PATH var. is unset.
 * 2. If file input is empty. */
bool	check_command(t_arguments *args)
{
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!ft_strcmp(BLANK, command_struct->command[0]))
		return (0);
	if (!command_struct)
		ft_shutdown(LST, 0, args);
	if (!is_executable(args))
		set_status(args, 127);
	if (error_input(args, command_struct))
		set_status(args, 1);
	if (args->status == 127 || args->status == 1)
	{
		errno = ENOENT;
		perror("minishell");
		close(args->wpipe[0]);
		close(args->wpipe[1]);
		return (0);
	}
	return (1);
}
