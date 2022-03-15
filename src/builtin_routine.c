/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:56:36 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/15 12:25:18 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	mnge_output_redirection(t_arguments *arg, t_command *command_struct)
{
	int	save_stdout;

	save_stdout = 0;
	if (command_struct->list_out)
	{
		generate_output(command_struct->list_out, \
		command_struct->flag_file, arg);
		if (!arg->file_output)
		{
			command_struct->flag_file = -1;
			printf("File or directory not found\n");
		}
		if (arg->flag_file_out)
			save_stdout = dup(1);
		if (command_struct->flag_file == 2)
			output_to_file_append(arg->file_output);
		else if (command_struct->flag_file == 1)
			output_to_file(arg->file_output);
	}
	return (save_stdout);
}

int
	get_stdout_copy(t_arguments *arg, t_command *command_struct)
{
	int			save_stdout;

	if (command_struct->list_in)
	{
		search_input(command_struct->list_in, arg);
		if (arg->file_input)
			input_from_file(arg->file_input);
	}
	save_stdout = mnge_output_redirection(arg, command_struct);
	return (save_stdout);
}

int
	builtin_routine(t_arguments *args, t_command *command_struct,
					int save_stdout)
{
	int	ret;
	int	i;

	set_status(args, 0);
	i = -1;
	ret = -1;
	while (++i < msh_num_builtins(args))
		if (!ft_strcmp(args->prog->builtin_str[i], command_struct->command[0]))
			ret = ((args->builtin_func[i])(command_struct->command, args));
	if (args->heredoc_list)
		ret = (heredoc_routine(args->heredoc_list));
	if (export_new_l_variables(command_struct->command, args))
		ret = 1;
	if (save_stdout)
	{
		//rl_replace_line("", 0);
		rl_redisplay();
		dup2(save_stdout, 1);
		close(save_stdout);
	}
	return (ret);
}
