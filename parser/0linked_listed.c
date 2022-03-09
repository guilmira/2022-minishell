/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0linked_listed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:55 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/09 11:02:40 by guilmira         ###   ########.fr       */
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
	/*if (!full_path)
		full_path[0] = getcwd(NULL, 0);
		new_string = ft_strdup(ft_strchr(getcwd(NULL, 0), '/'));
	else*/
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

/* char **create_new_table(char **table)
{
	char **new_table;
	int i = -1;
	
	new_table = ft_calloc(count_table(table), sizeof(char *));
	while (table[++i])
	{
		new_table[i] = ft_strdup(table[i]);
	}
	return (new_table); 
} */


int	count_command_words(char **table, int i)
{
	int words;

	words = 1;
	if (!table || !table[0])
		return (0);
	while (table[++i])
	{
		if (!ft_strncmp(table[i], "lex_", 4)) //ojo aquie en ve de lex_ odrias ser PIPE
			return (words);
		words++;
	}
	return (words);
}

/** PURPOSE : Number of command 0 is equivalent to first command. */
static int	obtain_position(char **table, int number_of_command)
{
	int	i;
	int	number_appeared;

	if (!number_of_command)
		return (0);
	i = -1;
	number_appeared = 0;
	while (table[++i])
	{
		
		if (!ft_strcmp(PIPE, table[i]))
			number_appeared++;
		if (number_appeared == number_of_command)
			return (i + 1);
	}
	return (i);
}

void	load_command_struct(t_command *command_struct, char **table, int i)
{
	int		j;
	char	**command_table;
	int words;

	i = obtain_position(table, i);
	words = count_command_words(table, i);
	/* printf("res: %i\n", i);
	printf("words: %i\n", words); */

	command_table = ft_calloc((count_command_words(table, i) + 1), sizeof(char *));
	if (!command_table)
		return ;
	j = 0;
	i = i - 1;
	while (table[++i])
	{
		if (!ft_strncmp("lex_", table[i], 4))
			break;
		command_table[j] = ft_strdup(table[i]);
		j++;
	}
	command_table[j] = NULL;
	command_struct->command = command_table;
}

/** PURPOSE : Builds linked list by allocating memory for a structure and
 * making that same structure the content of each node. Fills the path and 
 * the command fields. */
t_list	*load_linked_list(char **table, char **envp, int total_commands)
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
		load_command_struct(command_struct, table, i);
		//command_struct->command = ft_split(table[i], ' '); //UNICO CAMBIO EN ESTA FUNCION
		build_command_structure(command_struct, folders, envp);
		ft_lstadd_back(&lst, ft_lstnew(command_struct));
	}
	ft_free_split(folders);
	return (lst);
}
