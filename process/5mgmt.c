/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5mgmt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:31:20 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/14 10:01:03 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Output error with given value 2, close the program.
 *  Exit signal must be 0 by default */
void	ft_shut(char *str, int i)
{
	write(2, str, ft_strlen(str));
	exit(i);
}

/** PURPOSE : Free heap of structure. */
static void	free_msh_struct(t_command *command_struct)
{
	if (command_struct && command_struct->command)
		ft_free_split(command_struct->command);
	if (command_struct && command_struct->path)
		free_pointers(1, command_struct->path);
	if (command_struct && command_struct->list_in)
		ft_fullclear(command_struct->list_in);
	if (command_struct && command_struct->list_out)
		ft_fullclear(command_struct->list_out);
}

/** PURPOSE : clears linked list from first element to last, including content
 * Also frees internal struct memory. */
static void	ft_structclear(t_list *lst)
{
	t_list		*tmp;
	t_command	*command_struct;

	if (!lst)
		return ;
	tmp = NULL;
	command_struct = NULL;
	while (lst)
	{
		tmp = lst->next;
		if (lst->content)
			command_struct = lst->content;
		if (lst->content)
		{
			free_msh_struct(command_struct);
			free_pointers(1, command_struct);
			free(lst);
		}
		lst = tmp;
	}
}

/** PURPOSE : Free memory of program and close file descriptors.
 * For the function to properly work, all pointers have been
 * initialized to NULL at the beginning of the program. */
void	free_heap_memory(t_arguments *args)
{
	if (args)
	{
		if (args->argv)
			ft_free_split(args->argv);
		if (args->commands_lst && args->commands_lst->content != NULL)
			ft_structclear(args->commands_lst);
		if (args->heredoc_list && args->heredoc_list->content != NULL)
			ft_fullclear(args->heredoc_list);
		if (args->fds)
			free(args->fds);
		if (args->file_output)
			free(args->file_output);
		if (args->file_input)
			free(args->file_input);
		free_pointers(1, args->wpipe);
		free(args);
	}
}

/** PURPOSE : shutdown program freeing heap allocated memory. */
void	ft_shutdown(char *str, int i, t_arguments *args)
{
	perror("ERROR");
	free_heap_memory(args);
	ft_shut(str, i);
}
