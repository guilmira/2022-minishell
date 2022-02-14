/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 06:22:53 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/20 15:23:14 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **
	copy_array(char **dest, char **src)
{
	size_t	len;

	len = get_arr_len(src);
	dest = (char **)get_arr(len + 1, sizeof(char *));
	copy_arr_entries(dest, src, len);
	dest[len] = NULL;
	return (dest);
}

/** PURPOSE : Init program variable. */
t_prog	*initalize_prog(char **envp, char **builtin_str)
{
	t_prog	*prog;

	prog = ft_calloc(1, sizeof(t_prog));
	if (!prog)
		ft_shut(MEM, 0);
	prog->envp = copy_array(prog->envp, envp);
	init_builtins(builtin_str);
	prog->builtin_str = builtin_str;
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
	if (args->envp)
		ft_free_split(args->envp);
	args->envp = copy_array(args->envp, prog->envp);
	init_builtin_func_arr(args->builtin_func);
	args->status = prog->status;
	args->builtin_str = prog->builtin_str;
	return (args);
}
