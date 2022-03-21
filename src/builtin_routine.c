/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:56:36 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/21 13:19:42 by guilmira         ###   ########.fr       */
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



void create_file_heredoc(t_command *command_struct, t_arguments *args)
{

	int	fd_file;
	char *heredoc_str;
	char *path;
	t_list *end;
	
	if (args->here_output)
	{
		end = ft_lstlast(args->here_output);
		heredoc_str = end->content;
	}
	path = ft_strjoin(PATH_TMP, HEREDOC_FILE);
	fd_file = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	write(fd_file, heredoc_str, ft_strlen(heredoc_str));
	close(fd_file);
	command_struct->heredoc_file = path;
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
	if (export_new_l_variables(command_struct->command, args))
		ret = 1;
	if (!command_struct->command[0] || !ft_strcmp(BLANK, command_struct->command[0]))
		args->print_heredoc = false;
	if (args->print_heredoc && args->heredoc_list)
	{
		create_file_heredoc(command_struct, args);
		//print_heredoc(args);
	}
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
	{
		ret = heredoc_routine(args->heredoc_list, args);
	}
	save_stdout = get_stdout_copy(args, command_struct);
		
	ret = builtin_routine(args, command_struct, save_stdout, ret);
	return (ret);
}
