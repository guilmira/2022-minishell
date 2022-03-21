/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0alloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:00:25 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/21 15:18:50 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/** PURPOSE : Heredoc are found in table. */
int	heredoc_found(char **table, int *type, int i)
{
	while (table[++i])
	{
		if (type[i] == 0)
			break ;
		if (!ft_strcmp(HEREDOC, table[i]))
			return (1);
	}
	return (0);
}

/** PURPOSE : Obtain linked list with files (input) of pipe segment. */
t_list	*redirections_in(char **table, int *type, int i, t_arguments *args)
{
	char	*str;
	t_list	*list_in;

	str = NULL;
	list_in = NULL;
	i = obtain_position(table, i);
	i = i - 1;
	while (table[++i])
	{
		if (type[i] == 0)
			break ;
		if (!ft_strcmp(IN, table[i]))
		{
			if (heredoc_found(table, type, i))
				;
			else if (type[i + 1] == 2)
			{	
				str = ft_strdup(table[i + 1]);
				if (!str)
					ft_shutdown(str, i, args);
				ft_lstadd_back(&list_in, ft_lstnew(str));
			}
		}
	}
	return (list_in);
}

/** PURPOSE : Obtain linked list with files (input) of pipe segment. */
t_list	*delimeters_in(char **table, int *type, int i, t_arguments *args)
{
	char	*str;
	t_list	*list_delimeters;

	str = NULL;
	list_delimeters = NULL;
	i = obtain_position(table, i);
	i = i - 1;
	while (table[++i])
	{
		if (type[i] == 0)
			break ;
		if (!ft_strcmp(HEREDOC, table[i]))
		{
			if (type[i + 1] == 2)
			{	
				str = ft_strdup(table[i + 1]);
				if (!str)
					ft_shutdown(str, i, args);
				ft_lstadd_back(&list_delimeters, ft_lstnew(str));
			}
		}
	}
	return (list_delimeters);
}

/** PURPOSE : Obtain linked list with files (output) of pipe segment. */
t_list	*redirections_out(char **table, t_command	\
*command_struct, int i, t_arguments *args)
{
	char	*str;
	t_list	*list_out;

	str = NULL;
	list_out = NULL;
	i = obtain_position(table, i);
	i = i - 1;
	while (table[++i])
	{
		if (!ft_strcmp(PIPE, table[i]))
			break ;
		if (!ft_strcmp(APPEND, table[i]) || !ft_strcmp(OUT, table[i]))
		{
			command_struct->flag_file = 1;
			str = ft_strdup(table[i + 1]);
			if (!str)
				ft_shutdown(str, i, args);
			ft_lstadd_back(&list_out, ft_lstnew(str));
			if (!ft_strcmp(APPEND, table[i]))
				command_struct->flag_file = 2;
		}
	}
	return (list_out);
}

/** PURPOSE : Inti to Null command structure. */
void	struct_init(t_command *command_struct, int index)
{
	command_struct->index = index;
	command_struct->path = NULL;
	command_struct->command = NULL;
	command_struct->list_in = NULL;
	command_struct->list_out = NULL;
	command_struct->flag_file = 0;
	command_struct->list_delimeters = NULL;
	command_struct->heredoc_file = NULL;
}

/** PURPOSE : Corresponding numbers are:
 * 0	PIPE
 * 1	REDIRECT
 * 2	FILE
 * 3	APPEND
 * 4	HEREDOC
 * 5	COMMAND TOKEN
 * 6	EMPTY */
t_command	*alloc_command_struct(char **table, int *type, \
int i, t_arguments *args)
{
	t_list		*list_in;
	t_list		*list_out;
	t_command	*command_struct;
	t_list		*list_delimeters;

	list_in = NULL;
	list_out = NULL;
	command_struct = NULL;
	command_struct = ft_calloc(1, sizeof(t_command));
	if (!command_struct)
		ft_shutdown(MEM, 2, args);
	struct_init(command_struct, i);
	list_in = redirections_in(table, type, i, args);
	command_struct->list_in = list_in;
	list_out = redirections_out(table, command_struct, i, args);
	command_struct->list_out = list_out;

	//<< fin << done | << first << second
	list_delimeters = delimeters_in(table, type, i, args);
	command_struct->list_delimeters = list_delimeters;

	return (command_struct);
}
