/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0linked_listed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:55 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/24 15:25:01 by guilmira         ###   ########.fr       */
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
char	**get_env_path(char *envp[])
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
void	build_command_structure(t_command	*cmd_struct, \
char **folders, char **envp)
{
	char	*tmp;

	if (!cmd_struct)
		return ;
	if (!cmd_struct->command || !cmd_struct->command[0])
		return ;
	if (cmd_struct->command[0][0] == '.' && cmd_struct->command[0][1] == '/')
		cmd_struct->path = set_path(cmd_struct->command[0] + 2, folders, envp);
	else if ((ft_strchr(cmd_struct->command[0], '/')))
	{
		tmp = cmd_struct->command[0];
		cmd_struct->command[0] = ft_strdup(\
		ft_strrchr(cmd_struct->command[0], '/') + 1);
		cmd_struct->path = ft_strdup(tmp);
		free(tmp);
	}
	else
		cmd_struct->path = set_path(cmd_struct->command[0], \
		folders, envp);
}

/** PURPOSE : Builds linked list by allocating memory for a structure and
 * making that same structure the content of each node. Fills the path and 
 * the command fields. */
t_list	*load_linked_list(char **table, int *lexer_type, \
char **envp, t_arguments *args)
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
