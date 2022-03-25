/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 04:26:02 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/25 11:40:10 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_command *command_struct, t_arguments *args)
{
	int	i;
	int	ret;

	i = -1;
	ret = -1;
	while (++i < msh_num_builtins(args))
		if (!ft_strcmp(args->prog->builtin_str[i], command_struct->command[0])
			&& (ft_strlen(args->prog->builtin_str[i])
				== ft_strlen(command_struct->command[0])))
			ret = (((args->builtin_func[i])(command_struct->command, args)));
	if (ret == -1)
		return (0);
	else
		return (1);
}

int	builtin_detection(t_arguments *args)
{
	int			i;
	t_command	*cmd;

	i = -1;
	cmd = NULL;
	while (++i < args->total_commands)
	{
		cmd = get_cmd(args, i);
		if (is_builtin(cmd, args))
			return (1);
	}
	return (0);
}

/** PURPOSE : Simple parser of command line. */
int	pre_filter(char *line)
{
	if (pre_filter_simple(line))
		return (1);
	if (pre_filter_advanced(line))
		return (1);
	return (0);
}
