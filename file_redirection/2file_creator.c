/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2file_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:33:15 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/10 17:05:35 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : File is input type. 
 *  * 1 is for output, 2 is for input, 3 for append 
 * and 4 for heredoc. */
static int	input_type(int *ptr)
{
	if ((*ptr) == 1 || (*ptr) == 3)
		return (1);
	return (0);
}

static void	manage_input(int *ptr, char *file, t_arguments *args)
{
	args->flag_file_out = 1;
	if (args->file_output)
		free(args->file_output);
	args->file_output = ft_strdup(file);
	if (!args->file_output)
		ft_shutdown(MEM, 1, args);
	if ((*ptr) == 1)
		create_file(file, args);
	if ((*ptr) == 3)
	{
		create_file_append(file, args);
		args->flag_file_out = 2;
	}
}

static void	manage_output(char *file, t_arguments *args)
{
	if (args->file_input)
		free(args->file_input);
	args->file_input = ft_strdup(file);
	if (!args->file_input)
		ft_shutdown(MEM, 1, args);
}

static void	manage_heredoc(char *file, t_arguments *args)
{
	char *str;
	
	str = ft_strdup(file);
	if (!str)
		ft_shutdown(MEM, 1, args);
	ft_lstadd_back(&args->heredoc_list, ft_lstnew(str));
}

/** PURPOSE : Iterate list and create every single file as is needed. 
 *  Codes: 1 is for output, 2 is for input, 3 for append and 4 for heredoc. */
static void	create_output_files(t_list *list_files, \
t_list *list_type, t_arguments *args)
{
	int		*ptr;

	ptr = NULL;
	while (list_files)
	{
		ptr = list_type->content;
		if (input_type(ptr))
		{
			manage_input(ptr, list_files->content, args);
		}
		if ((*ptr) == 2)
		{
			manage_output(list_files->content, args);
			if (!file_exists(list_files->content))
			{
				args->flag_file_in = -1;
				break ;
			}
			args->flag_file_in = 1;
		}
		if ((*ptr) == 4)
			manage_heredoc(list_files->content, args);
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
