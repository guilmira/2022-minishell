/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:35:59 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/22 06:43:11 by guilmira         ###   ########.fr       */
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

/** PURPOSE : Detects first command on given argv. Then returns previous position. */
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
			break;
		}
	}
	return (i - 1);
}

/** PURPOSE : Boolean that evaluates if text is part of a command.
 * Such is the case on <echo "text"> or <cat "text">. */
static int is_following_text(char *previous, char *text)
{
	if (is_file_symb(text[0]))
		return (0);
	if (is_special(previous))
		return (1);
	return (0);
}

/** PURPOSE : Fills table with every command, including its command line options
 * 1. Detects first command and inserts it on position 0 of table.
 * 2. Checks if there is more content on argv, If there is, it will add it to the
 * command by using the following rules:
 * -> is it pipe? Do not add.
 * -> is it a sufix(command line option) or a text like echo "text". Then add
 * -> is it a command on its own? then it should go on next position of table. */
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
		else if (is_sufix(argv[i + 1][0]) || is_following_text(argv[i], argv[i + 1]))
			table[j] = build_new_string(table[j], argv[i + 1], args);
		/* else if (!is_command(argv, argv[i + 1], i + 1) && !is_file_symb(argv[i + 1][0]))
			table[j] = build_new_string(table[j], argv[i + 1], args); */
		else if (is_command(argv, argv[i + 1], i + 1))
			table[++j] = ft_strdup(argv[i + 1]);
	}
	table[++j] = NULL;
}

/** PURPOSE : Creates a table with a FULL COMMAND in each position. 
 * i.e.:
 * table[0] = "ls -la"
 * table[1] = "wc -l"
 * table[2] = "grep this is an example" */
static char	**split_commands(char **argv, t_arguments	*args)
{
	
	char	**table;
	int		total_commands;

	table = NULL;
	total_commands = count_commands(argv);
	table = ft_calloc(total_commands + 1, sizeof(char *));
	if (!table)
		ft_shut(MEM, 0);
	build_table(argv, table, args);
	return (table);
}

/** PURPOSE : Reads command line and allocates it into string.
 * If pointer line exists and is not empty, adds it to history. */
static char	*read_shell_line()
{
	char	*line;

	line = readline(MSHELL);
	if (!line)
		return (NULL);
	if (line[0])
		add_history(line);
	return (line);
}

/** PURPOSE : Reads command line. Loads arguments into structure. 
 * 1. Allocates memory for structure.
 * 2. Parses and rearranges arguments. i.e: "ls -la" will be a single arg.
 * 3. Counts number of total commands. i.e: "ls -la" "wc -l" = 2 total args.
 * 4. Creates linked list to manage any number of commands. */
void	shell_reader(char *envp[], t_arguments	*args)
{
	char		*line;
	char		**table;

	line = read_shell_line();
	if (!line)
		ft_shutdown(LINE, errno, args);
	args->status = 1;
	if (parser_line(line))
	{
		free(line);
		return ;
	}
	args->flag_execution = 1;
	args->argv = ft_split(line, ' ');
	free(line);
	table = split_commands(args->argv, args);
	args->total_commands = count_commands(args->argv);
	arg_reader(count_tokens(args->argv), table, envp, args);
	ft_free_split(table);
}
