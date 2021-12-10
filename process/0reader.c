/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0reader.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:55 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/10 10:38:10 by guilmira         ###   ########.fr       */
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

/** PURPOSE : Builds linked list by allocating memory for a structure and
 * making that same structure the content of each node. Fills the path and 
 * the command fields. */
static t_list	*load_linked_list(char *argv[], int mod, char *envp[], int coms)
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
	while (++i < coms)
	{
		command_struct = ft_calloc(1, sizeof(t_command));
		if (!command_struct)
		{
			ft_free_split(folders);
			return (NULL);
		}
		command_struct->command = ft_split(argv[i + mod], ' ');
		command_struct->path = set_path(command_struct->command[0], folders);
		ft_lstadd_back(&lst, ft_lstnew(command_struct));
	}
	ft_free_split(folders);
	return (lst);
}

/** PURPOSE : Load arguments into structure. 
 * 1. Allocates memory for structure.
 * 2. Checks whether program needs to take into account in/output files.
 * 3. Creates linked list to manage any number of commands */
t_arguments	*arg_reader(int argc, char *argv[], char *envp[])
{
	int			mod;
	t_arguments	*args;

	args = ft_calloc(1, sizeof(t_arguments));
	if (!args)
		ft_shut(MEM, 0);
	args->envp = envp;
	mod = file_management(argc, argv, args);
	args->commands_lst = load_linked_list(argv, mod, \
	envp, args->total_commands);
	if (!args->commands_lst)
		ft_shutdown(ARG, 0, args);
	return (args);
}
