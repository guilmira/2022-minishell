/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/11 10:53:43 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	fork_single_child(t_arguments *args)
{
	int	identifier;
	int	i;
	int	wstatus;

	identifier = fork();
	if ((identifier) == 0)
	{
		i = single_son(args);
		write_pipe_to(args->wpipe, &i);
	/*	free_heap_memory(args);
		ft_free_split(args->envp);
		ft_free_split(args->lenvp);
		ft_free_split(args->prog->envp);
		ft_free_split(args->prog->lenvp);*/
		exit(0);
	}
	else if (identifier > 0)
	{
		read_pipe_from(args->wpipe, &args->status);
		wait(&wstatus);
	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
}

/** PURPOSE : Executes fork function for a single command. */
int
	single_process(t_arguments *args)
{
	int			i;
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct->command)
		return (0);
	i = -1;
	while (++i < msh_num_builtins(args))
		if (!ft_strcmp(args->prog->builtin_str[i], command_struct->command[0]))
			return ((args->builtin_func[i])(command_struct->command, args));
	if (export_new_l_variables(command_struct->command, args))
		return (1);
	set_status(args, 0);
	if (pipe(args->wpipe) == -1)
	{
		perror("PIPE ERROR\n");
		set_status(args, 1);
		return (1);
	}
	fork_single_child(args);
	return (1);
}
