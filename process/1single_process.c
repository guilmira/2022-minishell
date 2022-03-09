/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 14:10:20 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes fork function for a single command. */
volatile sig_atomic_t shutdown_flag = 1;
void cleanupRoutine(int signal_number __attribute__((unused)))
{
	shutdown_flag = 0;
}

void
kill_child(int *status, int identifier, int ret)
{
	ret = kill(identifier, SIGTERM);
	if (ret == -1) {
		perror("kill");
		exit(EXIT_FAILURE);
	}
	if (waitpid(identifier, status, WUNTRACED | WCONTINUED) == -1) {
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

int
	single_process(t_arguments *args)
{
	int			i;
	int			wstatus;
	int			identifier;
	t_command	*command_struct;
	int			pipe_status;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct->command)
		return (0); //should we exit here??
	i = -1;
	while (++i < msh_num_builtins(args))
		if (!ft_strcmp(args->prog->builtin_str[i], command_struct->command[0]))
			return ((args->builtin_func[i])(command_struct->command, args));
	if (export_new_l_variables(command_struct->command, args))
		return (1);
	set_status(args, 0);
	pipe_status = pipe(args->wpipe);
	if (pipe_status == -1)
	{
		perror("PIPE ERROR\n");
		set_status(args, 1);
		return (1);
	}
	identifier = fork();
	if (identifier == 0)
	{
		i = single_son(args);
		write_child_status(args, &i);
		kill (getpid(), SIGKILL);
	}
	else if (identifier > 0)
	{
		wait(&wstatus);
		read_child_status(args);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (1);
}
