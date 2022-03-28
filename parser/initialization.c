/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 06:22:53 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/28 17:05:04 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **
	copy_array(char **dest, char **src, unsigned int extra_cells)
{
	size_t	len;

	len = get_arr_len(src);
	dest = (char **)get_arr(len + extra_cells, sizeof(char *));
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
	prog->envp = copy_array(prog->envp, envp, 1);
	prog->lenvp = malloc(1 * sizeof(char *));
	prog->lenvp[0] = NULL;
	init_builtins(builtin_str);
	prog->builtin_str = builtin_str;
	prog->status = 0;
	return (prog);
}

/** PURPOSE : Set variables to zero. */
void	variables_to_zero(t_arguments *args)
{
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
	args->heredoc_det = 0;
}

/** PURPOSE : Init arguments variable. */
t_arguments	*initialize_arg(t_prog *prog)
{
	t_arguments	*args;

	args = ft_calloc(1, sizeof(t_arguments));
	if (!args)
		ft_shut(MEM, 0);
	args->prog = prog;
	variables_to_zero(args);
	if (args->envp)
		ft_free_split(args->envp);
	args->envp = copy_array(args->envp, prog->envp, 1);
	if (args->lenvp)
		ft_free_split(args->lenvp);
	args->lenvp = copy_array(args->lenvp, prog->lenvp, 1);
	init_builtin_func_arr(args->builtin_func);
	args->status = prog->status;
	args->builtin_str = prog->builtin_str;
	args->wpipe = (int *)(malloc(2 * sizeof(int)));
	return (args);
}

int
	is_command(t_command *command_struct, t_arguments *args)
{
	if (!ft_strcmp(BLANK, command_struct->command[0]))
		return (1);
	if (is_builtin(command_struct, args))
		return (1);
	if (file_exists(command_struct->path))
		return (1);
	return (0);
}
