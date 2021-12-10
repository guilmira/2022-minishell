/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/09 15:09:31 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Close fork file pointer replica not to be used. */
int	prepare_process(int fd_to_close, int fd_to_prepare)
{
	close(fd_to_close);
	return (fd_to_prepare);
}

/** PURPOSE : Checks whether command exists and if it does,
 * returns full path to it. */
char	*set_path(char *command, char **folders)
{
	int		i;
	char	*command_path;
	char	*current_dir;

	command_path = NULL;
	current_dir = NULL;
	i = -1;
	while (folders[++i])
	{
		command_path = ft_strjoin(folders[i], command);
		if (file_exists(command_path))
			return (command_path);
		free(command_path);
	}
	current_dir = "/Users/guilmira/Desktop/pipex/";
	command_path = ft_strjoin(current_dir, command);
	if (file_exists(command_path))
		return (command_path);
	else
		free(command_path);
	return (NULL);
}


