/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 06:22:53 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/22 06:29:08 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Init program variable. */
t_prog	*initalize_prog(char **envp, char **builtin_str)
{
	t_prog	*prog;

	prog = ft_calloc(1, sizeof(t_prog));
	if (!prog)
		ft_shut(MEM, 0);
	prog->envp = envp;
	init_builtins(builtin_str);
	prog->builtin_str = builtin_str; //builtin_str has being declared on stack instead of at heap.
	// ^  couldn´t this bring problems??
	prog->status = 0;
	return (prog);
}

/** PURPOSE : Init arguments variable. */
t_arguments	*intialize_arg(t_prog *prog)
{
	t_arguments	*args;

	args = ft_calloc(1, sizeof(t_arguments));
	if (!args)
		ft_shut(MEM, 0);
	args->argv = NULL;
	args->commands_lst = NULL;
	args->flag_execution = 0;
	args->command_number = 0;
	args->total_commands = 0;
	args->fds = NULL;
	args->flag_file_in = 0;
	args->flag_file_out = 0;
	args->file_input = NULL;
	args->file_output = NULL;
	args->prog = prog;
	args->envp = prog->envp;
	init_builtin_func_arr(args->builtin_func);
	args->status = prog->status;
	args->builtin_str = prog->builtin_str;
	return (args);
}