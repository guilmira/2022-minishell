/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paralell_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 06:42:52 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/25 08:33:00 by guilmira         ###   ########.fr       */
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

int	manage_pipes(t_command *cmd, t_command *prev_cmd, int index, int last)
{
	if (index != last)
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
	identifier = fork();
	if (identifier == 0)
	{
			//ret = get_builtins_ret(args, cmd);
		manage_pipes(cmd, prev_cmd, index, args->total_commands - 1);
		
			/* if (ret >= 0 && !cmd->heredoc_result)
			{
				write_pipe_to(args->wpipe, &ret);
				free_heap_memory(args);
				exit(0);
			} */
		ret = (do_execve(args, cmd));
		write_pipe_to(args->wpipe, &ret);
		exit(0);
	}
	else if (identifier > 0)
	{
		index++;
		cmd = get_cmd(args, index);
		close(prev_cmd->pipes[WRITE_FD]);
		process_continue();
	}
}

/** PURPOSE : Executes fork function to run commands.
 * 1. Create first pipe. 
 * 2. Fork process in a loop, and inside each son process, run command.
 * 3. Continue running program until last fork. */
int	paralell_processing(t_arguments *args)
{
	int			i;
	pid_t		identifier;
	int 		ret;
	t_command	*cmd;
	t_command	*prev_cmd;
	int			index;
	
	cmd = NULL;
	prev_cmd = NULL;
	i = -1;
	while (++i < args->total_commands - 1)  
	{
		index = i;
		cmd = get_cmd(args, index);
		if (index != 0)
			prev_cmd = get_cmd(args, index - 1);
		if (pipe(cmd->pipes) == -1)
			set_status_and_shut(args, MSG);
		create_son(cmd, prev_cmd, index, args);
	}

		else if (identifier > 0)
		{
			cmd->pid = identifier;
			index = 1;
			prev_cmd = get_cmd(args, index - 1);
			cmd = get_cmd(args, index);

			close(prev_cmd->pipes[WRITE_FD]);//
			identifier = fork();
			if (identifier == 0)
			{
				//ret = get_builtins_ret(args, cmd);
				if (dup2(prev_cmd->pipes[READ_FD], STDIN_FILENO) == -1)//
					ft_shutdown(DUP_ERROR, 0, args);
				close(prev_cmd->pipes[READ_FD]);//
				/* if (ret >= 0 && !cmd->heredoc_result)
				{
					write_pipe_to(args->wpipe, &ret);
					free_heap_memory(args);
					exit(0);
				} */
				ret = (do_execve(args, cmd));
				write_pipe_to(args->wpipe, &ret);
					exit(0);
			}
			else if (identifier > 0)
			{
				cmd->pid = identifier;
				close(prev_cmd->pipes[READ_FD]); //me podria estar dejando en el proceso principalsin cerrar el de read.
				//read_pipe_from(args->wpipe, i);
				//mnge_status(args, (*i)); no se aplicarlo
			}
		}
		else
			set_status_and_shut(args, FORK_ERROR);

	//cuantos wait tiene que hacer,esa es la clave. tantos como hijos. 2 fork=2 wait.
	i = -1;
	while (++i < args->total_commands)  
	{
		cmd = get_cmd(args, i);
		waitpid(cmd->pid, &(cmd->control), 0);
	}
	return(1);
}