/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3single_son.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:52 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/07 16:08:37 by guilmira         ###   ########.fr       */
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

/** PURPOSE : Executes a one only forked proccess. */
int	single_son(t_arguments *args)
{
	t_command	*command_struct;
	char		*path;

	set_signal(1);
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shutdown(LST, 0, args);
	if (args->flag_file_in)
		input_form_file(args->file_input);
	if (args->flag_file_out == 2)
		output_to_file_append(args->file_output);
	else if (args->flag_file_out)
		output_to_file(args->file_output);
	set_status(args, 0);
	if (export_new_l_variables(command_struct->command, args))
		return (1);
	if (!(ft_strcmp(command_struct->command[0], "lex_HEREDOC")))
		return (heredoc_routine(command_struct));
	path = command_struct->path;
	if (!path)
		path = getcwd(NULL, 0);
	if (execve(path, command_struct->command, args->envp) == -1)
	{
		errno = ENOENT;
		perror("minishell");
	}
	return (1);
}
