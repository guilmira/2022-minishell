/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 06:42:52 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/28 13:02:16 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Creates required number of parallel son. */
static void	manage_pipes(t_command *cmd, t_command *prev_cmd, \
int index, t_arguments *args)
{
	int	last_index;

	last_index = args->total_commands - 1;
	if (index != last_index)
	{
		close(cmd->pipes[READ_FD]);
		if (dup2(cmd->pipes[WRITE_FD], STDOUT_FILENO) == -1)
			ft_shutdown(DUP_ERROR, 0, args);
		close(cmd->pipes[WRITE_FD]);
	}
	if (index != 0)
	{
		if (dup2(prev_cmd->pipes[READ_FD], STDIN_FILENO) == -1)
			ft_shutdown(DUP_ERROR, 0, args);
		close(prev_cmd->pipes[READ_FD]);
	}
}

//exec_builtin()

	//int i;

//SET STATUS
	//set_status(args, 0);

//SET FILES
	/* while (++i < msh_num_builtins(args))
	{
				if (!ft_strcmp(args->prog->builtin_str[i], cmd->command[0])
				&& (ft_strlen(args->prog->builtin_str[i])
				== ft_strlen(cmd->command[0])))
				ret = (((args->builtin_func[i])(cmd->command, args)));
	} */


/** PURPOSE : Creates required number of paralell son. */
static int	create_son(t_command *cmd, t_command *prev_cmd, \
int index, t_arguments *args)
{
	int		ret;
	int		last_index;
	pid_t	identifier;
			int	i;

	i = -1;
	last_index = args->total_commands - 1;
	identifier = fork();
	ret = 0;
	if (identifier == 0)
	{
		manage_pipes(cmd, prev_cmd, index, args);
		/* if (is_builtin(cmd, args))
		{
			exec_builtin();
		} */
		//else
			ret = (do_execve(args, cmd));
		exit(ret);
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
static void	create_pipe(t_command *cmd, int index, t_arguments *args)
{
	int	last_command_index;

	last_command_index = args->total_commands - 1;
	if (index != last_command_index)
		if (pipe(cmd->pipes) == -1)
			set_status_and_shut(args, MSG);
}

/** PURPOSE : Executes fork function to run commands.
 * 1. Create first pipe. 
 * 2. Fork process in a loop, and inside each son process, run command.
 * 3. Continue running program until last fork. */
int	processing(t_arguments *args)
{
	int			ret;
	int			index;
	t_command	*cmd;
	t_command	*prev_cmd;

	cmd = NULL;
	prev_cmd = NULL;
	index = -1;
	while (++index < args->total_commands)
	{
		cmd = get_cmd(args, index);
		if (index != 0)
			prev_cmd = get_cmd(args, index - 1);
		create_pipe(cmd, index, args);
		ret = create_son(cmd, prev_cmd, index, args);
	}
	close(prev_cmd->pipes[READ_FD]); //podria sobrar, probar.
	index = -1;
	while (++index < args->total_commands)
	{
		cmd = get_cmd(args, index);
		waitpid(cmd->pid, &(cmd->control), 0);
	}
	return (1);
}
