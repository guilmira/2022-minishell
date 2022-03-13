/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0linked_listed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:55 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/13 10:22:22 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Locates environment variable that starts with
 * the characters PATH= and splits it into a table. */
static char	**get_full_path(char *envp[])
{
	int		i;
	char	**hand_made_full_path;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i], ':'));
	hand_made_full_path = (char **)(malloc(2 * sizeof(char *)));
	hand_made_full_path[0] = getcwd(NULL, 0);
	hand_made_full_path[1] = NULL;
	return (hand_made_full_path);
}

/** PURPOSE : Reforms the string table by adding the char slash '/'. */
static char	**add_slash_to_path(char **full_path)
{
	int		i;
	char	*added_slash;

	i = -1;
	while (full_path[++i])
	{
		added_slash = ft_strjoin(full_path[i], "/");
		if (!added_slash)
		{
			ft_free_split(full_path);
			return (NULL);
		}
		free(full_path[i]);
		full_path[i] = added_slash;
	}
	return (full_path);
}

/** PURPOSE : Returns a string table with the direction of every single
 * folder where the commands might be contained. */
static char	**get_env_path(char *envp[])
{
	char	*new_string;
	char	**full_path;
	char	**corrected_path;

	full_path = get_full_path(envp);
	if (!full_path)
		return (NULL);
	new_string = ft_strdup(ft_strchr(full_path[0], '/'));
	if (!new_string)
	{
		ft_free_split(full_path);
		return (NULL);
	}
	free_pointers(1, full_path[0]);
	full_path[0] = new_string;
	corrected_path = add_slash_to_path(full_path);
	if (!corrected_path)
		return (NULL);
	return (corrected_path);
}

/** PURPOSE : Builds command and path for the structure.
 * Manages input commands such as /bin/ls.
 * Transforms it into the clean command and adjusts path. */
void	build_command_structure(t_command	*command_struct, \
char **folders, char **envp)
{
	char	*tmp;

	if (!command_struct)
		return ;
	if (!command_struct->command || !command_struct->command[0])
		return ;
	if ((ft_strchr(command_struct->command[0], '/')))
	{
		tmp = command_struct->command[0];
		command_struct->command[0] = ft_strdup(\
		ft_strrchr(command_struct->command[0], '/') + 1);
		command_struct->path = ft_strdup(tmp);
		free(tmp);
	}
	else
		command_struct->path = set_path(command_struct->command[0], \
		folders, envp);
}


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
			if (type[i + 1] == 2)
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

t_list	*redirections_out(char **table, t_command	*command_struct, int i, t_arguments *args)
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
				ft_shutdown(str, i, args); //esto recuerda la prueba de PATH. puedes alterar la flag y listo
			ft_lstadd_back(&list_out, ft_lstnew(str));
			if (!ft_strcmp(APPEND, table[i]))
				command_struct->flag_file = 2;
		}
	}
	return (list_out);
}

void	struct_init(t_command *command_struct, int index)
{
	command_struct->index = index;
	command_struct->path = NULL;
	command_struct->command = NULL;
	command_struct->list_in = NULL;
	command_struct->list_out = NULL;
	command_struct->flag_file = 0;
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
	return (command_struct);
}

/** PURPOSE : Builds linked list by allocating memory for a structure and
 * making that same structure the content of each node. Fills the path and 
 * the command fields. */
t_list	*load_linked_list(char **table, int *lexer_type, char **envp,  t_arguments *args)
{
	int			i;
	char		**folders;
	t_list		*lst;
	t_command	*command_struct;

	lst = NULL;
	folders = get_env_path(envp);
	if (!folders)
		return (NULL);
	i = -1;
	while (++i < args->total_commands)
	{
		command_struct = alloc_command_struct(table, lexer_type, i, args);
		load_command_struct(command_struct, table, i, args);
		build_command_structure(command_struct, folders, envp);
		ft_lstadd_back(&lst, ft_lstnew(command_struct));
	}
	ft_free_split(folders);
	return (lst);
}
