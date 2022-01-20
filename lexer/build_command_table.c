/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:53:32 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/20 15:23:48 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Creates new string that links full build of command. 
 * i.e.: "ls" and "-la" will become "ls -la". */
static char	*build_new_string(char *original, char *sufix, t_arguments	*args)
{
	char	*tmp;
	char	*new_string;

	if (!original)
		return (NULL);
	tmp = ft_strjoin(original, " ");
	if (!tmp)
		ft_shutdown(MEM, 0, args);
	free(original);
	new_string = ft_strjoin(tmp, sufix);
	if (!new_string)
		ft_shutdown(MEM, 0, args);
	free(tmp);
	return (new_string);
}

/** PURPOSE : Fills table with every command, including its command line options
 * 1. Detects first command and inserts it on position 0 of table.
 * 2. Checks if there is more content on argv, If there is, it will add it to the
 * command by using the following rules:
 * -> is it pipe? Do not add.
 * -> is it a sufix(command line option) or a text like echo "text". Then add
 * -> is it a command on its own? then it should go on next position. */
static void	build_command_table(char **lexer_table, char **table, t_arguments *args, int *type)
{
	int		i;
	int		j;
	char	*token;

	j = 0;
	i = 0;
	token = NULL;
	table[j] = ft_strdup(lexer_table[0]);
	while (lexer_table[++i])
	{
		token = lexer_table[i];
		if (!type[i]) //is pipe
			j++;
		else if (type[i] != 5)
			;
		else if (!type[i - 1])
			table[j] = ft_strdup(lexer_table[i]);
		else
			table[j] = build_new_string(table[j], token, args);
	}
	table[++j] = NULL;
}

/** PURPOSE : Count total number of pipes. */
static int	count_pipes(char **lexer_table)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (lexer_table[++i])
		if (!ft_strcmp(lexer_table[i], PIPE))
			j++;
	return (j);
}

/** PURPOSE : Creates a table with a FULL COMMAND in each position. 
 * i.e.:
 * table[0] = "ls -la"
 * table[1] = "wc -l"
 * table[2] = "grep this is an example" */
char	**get_command_table(char **lexer_table, t_arguments *args, int *type)
{
	char	**table;
	int		pipes_number;

	table = NULL;
	pipes_number = count_pipes(lexer_table);
	args->total_commands = pipes_number + 1;
	table = ft_calloc(args->total_commands + 1, sizeof(char *));
	if (!table)
		ft_shutdown(MEM, errno, args);
	build_command_table(lexer_table, table, args, type);
	return (table);
}
