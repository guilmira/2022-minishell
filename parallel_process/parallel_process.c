/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 06:42:52 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/25 10:52:59 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define READ_FD 0
#define WRITE_FD 1


t_command	*get_cmd(t_arguments *args, int index)
{
	t_command	*cmd;

	cmd = ft_lst_position(args->commands_lst, index);
	if (!cmd || !cmd->command)
		ft_shutdown(LST, 0, args);
	return (cmd);
}

void	manage_pipes(t_command *cmd, t_command *prev_cmd, int index, t_arguments *args)
{
	int last_index;
	
	last_index = args->total_commands - 1;
	if (index != last_index)
	{
		close(cmd->pipes[READ_FD]);//
		if (dup2(cmd->pipes[WRITE_FD], STDOUT_FILENO) == -1)//
			ft_shutdown(DUP_ERROR, 0, args);
		close(cmd->pipes[WRITE_FD]);//
	}
	if (index != 0)
	{
		if (dup2(prev_cmd->pipes[READ_FD], STDIN_FILENO) == -1)//
			ft_shutdown(DUP_ERROR, 0, args);
		close(prev_cmd->pipes[READ_FD]);//
	}
	
}

int	create_son(t_command *cmd, t_command *prev_cmd, int index, t_arguments *args)
{
	pid_t		identifier;
	int last_index;
	int	ret;

	last_index = args->total_commands - 1;
	identifier = fork();
	ret = 0;
	if (identifier == 0)
	{
		manage_pipes(cmd, prev_cmd, index, args);
		ret = (do_execve(args, cmd));
		exit(0);
	}
	else if (identifier > 0)
	{
		cmd->pid = identifier;
		if (index != last_index)
			close(cmd->pipes[WRITE_FD]);
		if (index != 0)
			close(prev_cmd->pipes[READ_FD]);
		return (ret);
	}
	else
		set_status_and_shut(args, FORK_ERROR);
	return (ret);
}

/** PURPOSE : Creates a pipe, except in the case where the last
 * command of the command line is being executed. */
void create_pipe(t_command *cmd, int counter, t_arguments *args)
{
	int last_command_index;

	last_command_index = args->total_commands - 1;
	if (counter != last_command_index)
	{
		if (pipe(cmd->pipes) == -1)
			set_status_and_shut(args, MSG);
	}
}

/** PURPOSE : Executes fork function to run commands.
 * 1. Create first pipe. 
 * 2. Fork process in a loop, and inside each son process, run command.
 * 3. Continue running program until last fork. */
int	paralell_processing(t_arguments *args)
{
	int			i;
	int 		ret;
	t_command	*cmd;
	t_command	*prev_cmd;
	int			index;
	
	cmd = NULL;
	prev_cmd = NULL;
	i = -1;
	while (++i < args->total_commands)  
	{
		index = i;
		cmd = get_cmd(args, index);
		if (index != 0)
			prev_cmd = get_cmd(args, index - 1);
		create_pipe(cmd, i, args);
		ret = create_son(cmd, prev_cmd, index, args);
	}
	close(prev_cmd->pipes[READ_FD]); //podria sobrar, probar.
	
	
	//cuantos wait tiene que hacer,esa es la clave. tantos como hijos. 2 fork=2 wait.
	i = -1;
	while (++i < args->total_commands)  
	{
		cmd = get_cmd(args, i);
		waitpid(cmd->pid, &(cmd->control), 0);
	}

	return(1);
}