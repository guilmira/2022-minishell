/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1single_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 08:20:45 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 10:50:12 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Executes fork function for a single command. */
int
	single_process(t_arguments *args)
{
	int			i;
	int			status;
	int			identifier;
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
//	g_rv = 1;
	set_status(args, 0);
	//printf("status before fork = %d\n", args->status); //delete
	//printf("errno before fork = %d\n", errno); //delete

	int writepipe[2];
	int b;
	b = pipe(writepipe);

	identifier = fork();
	if (identifier == 0)
	{
		int	x;
		x = single_son(args);
		close(writepipe[0]);
		write(writepipe[1], &x, sizeof(int));
		close(writepipe[1]);
		exit(0);
	}
	else if (identifier > 0)
	{
		wait(&status);
		close(writepipe[1]);
		read(writepipe[0], &args->status, sizeof(int));
		close(writepipe[0]);
		//printf("status after wait = %d\n", args->status); //delete
		//printf("grv after wait = %d\n", g_rv); //delete

	}
	else
		ft_shutdown(FORK_ERROR, 0, args);
	return (1);
}
