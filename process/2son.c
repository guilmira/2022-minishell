/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/08 12:44:35 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Recieves input from file if needed. */
static void	input_form_file(char *path)
{
	int	fd_file;

	fd_file = open(path, O_RDONLY);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDIN_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
}

/** PURPOSE : Sends output to file if needed. */
static void	output_to_file(char *path)
{
	int	fd_file;

	fd_file = open(path, O_WRONLY | O_CREAT, FULL_PERMISSIONS);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
}

/** PURPOSE : Executes first forked proccess. The only thing
 * that it takes into account is if input comes from file. */
void	first_son(t_arguments *args)
{
	int			fd_write;
	t_command	*command_struct;

	
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shutdown(LST, 0, args);
	fd_write = prepare_process(args->fds[0], args->fds[1]);
	if (args->flag_file)
		input_form_file(args->file_input);
	if (dup2(fd_write, STDOUT_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(fd_write);
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shutdown(EXE_ERROR, 0, args);
}

/** PURPOSE : Executes first forked proccess. The only thing
 * that it takes into account is if output comes from file. */
void	last_son(int index, t_arguments *args)
{	
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shutdown(LST, 0, args);
	if (dup2(args->fds[index], STDIN_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(args->fds[index]);
	if (args->flag_file)
		output_to_file(args->file_output);
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shutdown(EXE_ERROR, 0, args);
}
