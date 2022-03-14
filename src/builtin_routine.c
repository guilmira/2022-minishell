/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 21:56:36 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/14 21:56:37 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	builtin_routine(t_arguments *args, t_command *command_struct,
					int save_stdout)
{
	int	ret;
	int	i;

	set_status(args, 0);
	i = -1;
	ret = -1;
	while (++i < msh_num_builtins(args))
		if (!ft_strcmp(args->prog->builtin_str[i], command_struct->command[0]))
			ret = ((args->builtin_func[i])(command_struct->command, args));
	if (args->heredoc_list)
		ret = (heredoc_routine(args->heredoc_list));
	if (export_new_l_variables(command_struct->command, args))
		ret = 1;
	if (save_stdout)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		dup2(save_stdout, 1);
		close(save_stdout);
	}
	return (ret);
}
