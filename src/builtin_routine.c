/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:56:36 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/17 13:15:54 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	mnge_output_redirection(t_arguments *arg, t_command *command_struct)
{
	int	save_stdout;

	save_stdout = 0;
	if (command_struct->list_out || arg->output_builtin)
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

	save_stdout = mnge_output_redirection(arg, command_struct);
	return (save_stdout);
}

void
	print_heredoc(const t_arguments *args)
{
	int		i;
	int		j;
	t_list	*temp;

	i = 0;
	j = ft_lstsize(args->here_output);
	temp = args->here_output;
	while (i < j && temp->content)
	{
		printf("%s", (char *)temp->content);
		temp = temp->next;
		i++;
	}
}

int
	builtin_routine(t_arguments *args, t_command *command_struct,
					int save_stdout, int ret)
{
	int	i;

	set_status(args, 0);
	i = -1;
	while (++i < msh_num_builtins(args))
		if (!ft_strcmp(args->prog->builtin_str[i], command_struct->command[0]))
			ret = (((args->builtin_func[i])(command_struct->command, args)));
	/*if (!ret)
		return (ret);*/
	if (export_new_l_variables(command_struct->command, args))
		ret = 1;
	if (args->print_heredoc)
		print_heredoc(args);
	if (save_stdout)
	{
		dup2(save_stdout, 1);
		close(save_stdout);
	}
	return (ret);
}

int
	get_builtins_ret(t_arguments *args, t_command *command_struct)
{
	int		ret;
	int		save_stdout;

	ret = -1;
	if (args->heredoc_list)
		ret = heredoc_routine(args->heredoc_list, args);
	save_stdout = get_stdout_copy(args, command_struct);
	ret = builtin_routine(args, command_struct, save_stdout, ret);
	return (ret);
}
