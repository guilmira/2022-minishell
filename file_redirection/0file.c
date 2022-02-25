/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0file.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 08:43:46 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/25 11:24:22 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Adds name of the list to files. */
static void	prepare_file(char *content, t_list **list_files, t_arguments *args)
{	
	char	*str;
	
	str = NULL;
	str = ft_strdup(content);
	if (!str)
		ft_shutdown(MEM, 0, args);
	ft_lstadd_back(list_files, ft_lstnew(str));
}

/** PURPOSE : Assign a number to each of the elements of the list. 
 * 1 is for output, 2 is for input, 3 for append and 4 for heredoc. */
static void assign_type(char *content, t_list **list_type, t_arguments *args)
{
	int		*ptr;

	ptr = NULL;
	ptr = ft_calloc(1, sizeof(int));
	if (!ptr)
		ft_shutdown(MEM, 0, args);
	*ptr = -1;
	if (!ft_strcmp(content, OUT))
		*ptr = 1;
	else if (!ft_strcmp(content, IN))
		*ptr = 2;
	else if (!ft_strcmp(content, APPEND))
		*ptr = 3;
	else if (!ft_strcmp(content, HEREDOC))
		*ptr = 4;
	ft_lstadd_back(list_type, ft_lstnew(ptr));
}

/** PURPOSE : Load arguments files into structure. 
 * 1. Checks whether files are given as parameter.
 * 2. Sets adsresses to input and output files (as a linked list).
 * 3. Sets some of the values of "args" struct. */
void	management_file(char **table, t_arguments *args)
{
	int		i;
	t_list	*list_files;
	t_list	*list_type;

	list_files = NULL;
	list_type = NULL;
	i = -1;
	while (table[++i])
	{
		if (!ft_strcmp(table[i], OUT) || !ft_strcmp(table[i], APPEND) || !ft_strcmp(table[i], IN) || !ft_strcmp(table[i], HEREDOC))
		{
			prepare_file(table[i + 1], &list_files, args);
			assign_type(table[i],  &list_type, args);
		}
	}
	//provisional
	int  *ptr;
	file_setup(list_files, list_type, args);
	while (list_files)
	{
		ptr = list_type->content;
		/* printf("lista: %s\n", list_files->content);
		printf("tipo: %i\n", *ptr); */
		list_files = list_files->next;
		list_type = list_type->next;
	}
	ft_fullclear(list_files);
	ft_fullclear(list_type);
}