/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:27 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/07 16:00:38 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Close fork file pointer replica not to be used. */
int	prepare_process(int fd_to_close, int fd_to_prepare)
{
	close(fd_to_close);
	return (fd_to_prepare);
}

/** PURPOSE : Creates string with needed adress. */
static char	*obtain_current_directory_adress(char **envp)
{
	int		i;
	char	*str;
	char	*full_address;

	i = -1;
	str = NULL;
	full_address = NULL;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PWD=", 4))
			full_address = ft_strdup(&envp[i][4]);
	str = ft_strjoin(full_address, "/");
	free(full_address);
	return (str);
}

/** PURPOSE : Checks whether command exists and if it does,
 * returns full path to it. */
char	*set_path(char *command, char **folders, char **envp)
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
	current_dir = obtain_current_directory_adress(envp);
	command_path = ft_strjoin(current_dir, command);
	free(current_dir);
	if (file_exists(command_path))
		return (command_path);
	else
		free(command_path);
	return (NULL);
}
