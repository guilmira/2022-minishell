/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6file_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:10:20 by guilmira          #+#    #+#             */
/*   Updated: 2022/04/10 12:36:55 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Recieves input from file if needed. */
void	input_from_file(char *path)
{
	int	fd_file;

	fd_file = open(path, O_RDONLY);
	if (fd_file < 0)
		ft_shut_specific(FILE_ERROR, 1);
	if (dup2(fd_file, STDIN_FILENO) == -1)
		ft_shut_specific(DUP_ERROR, 0);
	close(fd_file);
}

/** PURPOSE : Sends output to file if needed. */
void	output_to_file(char *path)
{
	int	fd_file;

	if (!path)
		return ;
	fd_file = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		return ;
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		ft_shut_specific(DUP_ERROR, 0);
	close(fd_file);
}

/** PURPOSE : Sends output to file if needed append. */
void	output_to_file_append(char *path)
{
	int	fd_file;

	if (!path)
		return ;
	fd_file = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		return ;
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		ft_shut_specific(DUP_ERROR, 0);
	close(fd_file);
}

void
	father_process_routine(t_arguments *args,
		int last_index, int *i, int *wstatus)
{
	close(args->fds[last_index]);
	read_pipe_from(args->wpipe, i);
	wait(wstatus);
	mnge_status(args, (*i));
}
