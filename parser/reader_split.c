/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:53:32 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/04 12:09:08 by guilmira         ###   ########.fr       */
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

/** PURPOSE : Detects first command on given argv. 
 * Then returns previous position. */
static int	find_first_command(char **argv, char **table, t_arguments	*args)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (is_command(argv, argv[i], i))
		{
			table[0] = ft_strdup(argv[i]);
			if (!table [0])
				ft_shutdown(MEM, 0, args);
			break ;
		}
	}
	return (i - 1);
}

/** PURPOSE : Fills table with every command, including its command line options
 * 1. Detects first command and inserts it on position 0 of table.
 * 2. Checks if there is more content on argv, If there is, it will add it to the
 * command by using the following rules:
 * -> is it pipe? Do not add.
 * -> is it a sufix(command line option) or a text like echo "text". Then add
 * -> is it a command on its own? then it should go on next position. */
static void	build_table(char **argv, char **table, t_arguments	*args)
{
	int	i;
	int	j;

	j = 0;
	i = find_first_command(argv, table, args);
	while (argv[++i])
	{
		if (!argv[i + 1])
			break ;
		if (is_pipe(argv[i + 1][0]))
			;
		else if (is_sufix(argv[i + 1][0]) \
		|| is_following_text(argv[i], argv[i + 1]))
			table[j] = build_new_string(table[j], argv[i + 1], args);
		/* else if (!is_command(argv, argv[i + 1], i + 1) && !is_file_symb(argv[i + 1][0]))
			table[j] = build_new_string(table[j], argv[i + 1], args); */
		else if (is_command(argv, argv[i + 1], i + 1))
			table[++j] = ft_strdup(argv[i + 1]);
	}
	table[++j] = NULL;
}

/** PURPOSE : Count total number of commands. */
static int	count_commands(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (argv[++i])
		if (is_command(argv, argv[i], i))
			j++;
	return (j);
}

/** PURPOSE : Creates a table with a FULL COMMAND in each position. 
 * i.e.:
 * table[0] = "ls -la"
 * table[1] = "wc -l"
 * table[2] = "grep this is an example" */
char	**split_commands(char **argv, t_arguments *args)
{
	char	**table;

	table = NULL;
	args->total_commands = count_commands(args->argv);
	table = ft_calloc(args->total_commands + 1, sizeof(char *));
	if (!table)
		ft_shut(MEM, 0);
	build_table(argv, table, args);
	return (table);
}
