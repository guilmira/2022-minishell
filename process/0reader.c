/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0reader.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:55 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/09 12:58:36 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Locates environment variable that starts with
 * the characters PATH= and splits it into a table. */
static char	**get_full_path(char *envp[])
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i], ':'));
	return (NULL);
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
	free(full_path[0]);
	full_path[0] = new_string;
	corrected_path = add_slash_to_path(full_path);
	if (!corrected_path)
		return (NULL);
	return (corrected_path);
}

/** PURPOSE : Builds command and path for the structure.
 * Manages input commands such as /bin/ls.
 * Transforms it into the clean command and adjusts path. */
void	build_command_structure(t_command	*command_struct, char **folders, char **envp)
{
	char	*tmp;

	if ((ft_strchr(command_struct->command[0], '/')))
	{
		tmp = command_struct->command[0];
		command_struct->command[0] = ft_strdup(ft_strrchr(command_struct->command[0], '/') + 1);
		command_struct->path = ft_strdup(tmp);
		free(tmp);
	}
	else
		command_struct->path = set_path(command_struct->command[0], folders, envp);
}

/** PURPOSE : Builds linked list by allocating memory for a structure and
 * making that same structure the content of each node. Fills the path and 
 * the command fields. */
static t_list	*load_linked_list(char **table, char **envp, int total_commands)
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
	while (++i < total_commands)
	{
		command_struct = ft_calloc(1, sizeof(t_command));
		if (!command_struct)
		{
			ft_free_split(folders);
			return (NULL);
		}
		command_struct->command = ft_split(table[i], ' ');
		build_command_structure(command_struct, folders, envp);
		ft_lstadd_back(&lst, ft_lstnew(command_struct));
	}
	ft_free_split(folders);
	return (lst);
}

/** PURPOSE : Load arguments into structure. 
 * 1. Allocates memory for structure.
 * 2. Checks whether program needs to take into account in/output files.
 * 3. Creates linked list to manage any number of commands */
void	arg_reader(int argc, char **table, char *envp[], t_arguments *args)
{
	file_management(argc, args->argv, args);
	args->commands_lst = load_linked_list(table, envp, args->total_commands);
	if (!args->commands_lst)
		ft_shutdown(ARG, 0, args);
}
