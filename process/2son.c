/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/01 13:24:54 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Call signal handler in child processes. */
/* static void	signal_management_sons(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
} */
//TODO, keep shell in execution

int
heredoc_routine(t_command *command_struct);

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

	fd_file = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
}

static void	output_to_file_append(char *path)
{
	int	fd_file;

	fd_file = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
}

/** PURPOSE : Executes first forked proccess. The only thing
 * that it takes into account is if input comes from file. */
int
	first_son(t_arguments *args)
{
	int			i;
	int			fd_write;
	t_command	*command_struct;
	
	set_signal(1);
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct && !command_struct->command)
		ft_shutdown(LST, 0, args);
	fd_write = prepare_process(args->fds[0], args->fds[1]);
	if (args->flag_file_in)
		input_form_file(args->file_input);
	if (dup2(fd_write, STDOUT_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(fd_write);
	i = 0;
	while (i < msh_num_builtins(args))
	{
		if (ft_strcmp(command_struct->command[0], args->prog->builtin_str[i]) == 0)
			return ((args->builtin_func[i])(command_struct->command, args));
		i++;
	}
	set_status(args, 0);
	if (!(ft_strcmp(command_struct->command[0], "lex_HEREDOC")))
		return (heredoc_routine(command_struct));
	return (execve(command_struct->path, command_struct->command, args->envp));
}

/** PURPOSE : Executes first forked proccess. The only thing
 * that it takes into account is if output comes from file. */
int
	last_son(int index, t_arguments *args)
{	
	t_command	*command_struct;
	int			i;

	set_signal(1);
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct && !command_struct->command)
		ft_shutdown(LST, 0, args);
	if (dup2(args->fds[index], STDIN_FILENO) == -1)
		ft_shutdown(DUP_ERROR, 0, args);
	close(args->fds[index]);
	if (args->flag_file_out == 2)
		output_to_file_append(args->file_output);
	else if (args->flag_file_out)
		output_to_file(args->file_output);
	i = 0;
	while (i < msh_num_builtins(args))
	{
		if (ft_strcmp(command_struct->command[0], args->prog->builtin_str[i]) == 0)
			return ((args->builtin_func[i])(command_struct->command, args));
		i++;
	}
	set_status(args, 0);
	if (!(ft_strcmp(command_struct->command[0], "lex_HEREDOC")))
		return (heredoc_routine(command_struct));
	return (execve(command_struct->path, command_struct->command, args->envp));
}

/** PURPOSE : Executes a one only forked proccess. */
int	single_son(t_arguments *args)
{
	t_command	*command_struct;

	set_signal(1);
	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	printf("HERE %s\n", get_env_var(args->envp, "PATH"));
	if (!command_struct)
		ft_shutdown(LST, 0, args);
 	if (args->flag_file_in)
		input_form_file(args->file_input);
	if (args->flag_file_out == 2)
		output_to_file_append(args->file_output);
	else if (args->flag_file_out)
		output_to_file(args->file_output);
	set_status(args, 0);
	if (!(ft_strcmp(command_struct->command[0], "lex_HEREDOC")))
		return (heredoc_routine(command_struct));
	//printf("fin %s y %s\n", command_struct->path, command_struct->command[1]);
	if (execve(command_struct->path, command_struct->command, args->envp) == -1)
	{
		set_status(args, 1);
		ft_shutdown(EXE_ERROR, 0, args);
	}
	return (1);
}
