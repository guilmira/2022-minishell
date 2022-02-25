/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1file_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 08:51:24 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/25 11:11:12 by guilmira         ###   ########.fr       */
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

// TODO, question. if adding after O_CREAT, FULL_PERMISSIONS, overwrite stops working

/** PURPOSE : Sends output to file if needed. 
 * //S_IRWXU File permission bits. Read, Write, eXecute. */
static void	create_file(char *path, t_arguments *args)
{
	int	fd_file;

	fd_file = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		ft_shutdown(FILE_ERROR, 1, args);
	close(fd_file);
}

/** PURPOSE : Sends output to file if needed. 
 * //S_IRWXU File permission bits. Read, Write, eXecute. */
static void	create_file_append(char *path, t_arguments *args)
{
	int	fd_file;

	fd_file = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd_file < 0)
		ft_shutdown(FILE_ERROR, 1, args);
	close(fd_file);
}

/** PURPOSE : Iterate list and create every single file as is needed. 
 *  Codes: 1 is for output, 2 is for input, 3 for append and 4 for heredoc. */
static void	create_output_files(t_list *list_files, t_list *list_type, t_arguments *args)
{
	int		*ptr;
	char	*file;

	ptr = NULL;
	while (list_files)
	{
		file = list_files->content;
		ptr = list_type->content;
		if ((*ptr) == 1 || (*ptr) == 3)
		{
			args->flag_file_out = 1;
			args->file_output = file;
			if ((*ptr) == 1)
				create_file(file, args);
			if ((*ptr) == 3)
				create_file_append(file, args);
		}
		if ((*ptr) == 2)
		{
			args->file_input = list_files->content;
			if (!file_exists(file))
			{
				args->flag_file_in = -1;
				break;
			}
			args->flag_file_in = 1;
		}
		list_files = list_files->next;
		list_type = list_type->next;
	}
}

/** PURPOSE : Load structure with due arguments.
 * Also create files if needed. */
void	file_setup(t_list *list_files, t_list *list_type, t_arguments *args)
{
	create_output_files(list_files, list_type, args);
	
}