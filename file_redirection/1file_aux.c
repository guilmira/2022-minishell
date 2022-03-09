/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1file_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 08:51:24 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 14:35:15 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Does the path of the command exist? Returns bool. */
int	file_exists(char *str)
{
	int	fp;

	fp = open(str, O_RDONLY);
	if (fp == -1)
		return (0);
	close(fp);
	return (1);
}

/** PURPOSE : Sends output to file if needed. 
 * //S_IRWXU File permission bits. Read, Write, eXecute. */
void	create_file(char *path, t_arguments *args)
{
	int	fd_file;

	fd_file = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		ft_shutdown(FILE_ERROR, 1, args);
	close(fd_file);
}

/** PURPOSE : Sends output to file if needed. 
 * //S_IRWXU File permission bits. Read, Write, eXecute. */
void	create_file_append(char *path, t_arguments *args)
{
	int	fd_file;

	fd_file = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		ft_shutdown(FILE_ERROR, 1, args);
	close(fd_file);
}
