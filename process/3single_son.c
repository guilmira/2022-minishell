/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3single_son.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:52 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/13 11:13:38 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Cleans heap in case of error. */
/*static void	error_single_son(t_arguments *args)
{
	set_status(args, 1);
	ft_free_split(args->envp);
	ft_free_split(args->lenvp);
	ft_shutdown(EXE_ERROR, 0, args);
}*/

char *
	get_path(t_command *command_struct)
{
	char	*path;

	path = command_struct->path;
	if (!path)
		path = getcwd(NULL, 0);
	return (path);
}

int
	do_execve(t_arguments *args, t_command *command_struct)
{
	char	*path;

	set_status(args, 0);
	path = get_path(command_struct);
	if (is_blank(args->command_number, args))
		return (0);
	else
		execve(path, command_struct->command, args->envp);
	errno = ENOENT;
	perror("minishell");
	return (127);
}

/** PURPOSE : Executes a one only forked proccess. */
int	single_son(t_arguments *args)
{
	t_command	*command_struct;

	set_signal(1);
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shutdown(LST, 0, args);
	manage_input_redirection(args);
	manage_output_redirection(args);
	return (do_execve(args, command_struct));
}
