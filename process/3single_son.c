/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3single_son.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:52 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/22 15:13:01 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *
	get_path(t_command *command_struct, bool *do_clean_path)
{
	char	*path;

	path = command_struct->path;
	if (!path)
	{
		path = getcwd(NULL, 0);
		*do_clean_path = true;
	}
	return (path);
}

int
	do_execve(t_arguments *args, t_command *command_struct)
{
	char	*path;
	bool	do_clean_path;

	do_clean_path = false;
	set_status(args, 0);
	path = get_path(command_struct, &do_clean_path);
	command_file_setup(command_struct, args);
	
	command_struct->command[0] = strdup("script.sh"); //option1
	//option 2, comment above line
	printf("aqui %s\n", command_struct->command[0]);
	printf("aqui %s\n", command_struct->command[1]);
	if (is_blank(args->command_number, args))
		return (0);
	else
		execve(path, command_struct->command, args->envp);
	if (do_clean_path)
		free(path);
	errno = ENOENT;
	perror("minishell");
	return (127);
}

/** PURPOSE : Executes a one only forked proccess. */
int	single_son(t_arguments *args)
{
	t_command	*command_struct;

	set_signal(1);
	command_struct = NULL;
	
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shutdown(LST, 0, args);
	return (do_execve(args, command_struct));
}
