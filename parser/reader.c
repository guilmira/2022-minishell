/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:35:59 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/18 08:16:22 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Creates new string that links full build of command. 
 * i.e.: "ls" and "-la" will become "ls -la". */
static char	*build_new_string(char *original, char *sufix)
{
	char	*tmp;
	char	*new_string;

	if (!original)
		return (NULL);
	tmp = ft_strjoin(original, " ");
	if (!tmp)
		ft_shut(MEM, 0); //TODO perror
	free(original);
	new_string = ft_strjoin(tmp, sufix);
	if (!new_string)
		ft_shut(MEM, 0); //TODO perror
	free(tmp);
	return (new_string);
}

/** PURPOSE : Creates a table with a FULL COMMAND in each position. 
 * i.e.:
 * table[0] = "ls -la"
 * table[1] = "wc -l"
 * table[2] = "grep this is an example" */
static char	**split_commands(char **argv)
{
	int		i;
	int		j;
	char	**table;
	int		total_commands;

	table = NULL;
	total_commands = count_commands(argv);
	table = ft_calloc(total_commands + 1, sizeof(char *));
	if (!table)
		ft_shut(MEM, 0); //todo: use errorno
	j = 0;
	i = -1;
	table[0] = ft_strdup(argv[0]);
	while (argv[++i]) //LOGIC CAN BE IMPROVED
	{
		if (!argv[i + 1])
			break ;
		if (!is_command(argv[i + 1]) && !is_pipe(argv[i + 1][0]))
			table[j] = build_new_string(table[j], argv[i + 1]);
		else if (is_pipe(argv[i + 1][0]))
			;
		else if (is_command(argv[i + 1]))
			if (argv[i + 1])
				table[++j] = ft_strdup(argv[i + 1]);
	}
	table[++j] = NULL;
	return (table);
}

/** PURPOSE : Reads command line and allocate it into string. */
static char	*read_shell_line()
{
	char	*line;

	line = readline("msh keys_testing> ");
	/* gnl = get_next_line(0, &line);
	if (gnl == -1)
	{
		//perror("Error:"); should work, but must be well tested
		printf("Error at GNL\n");
		exit((EXIT_FAILURE));
	} */
	if (!line)
		return (NULL);
	if (!line[0])
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/** PURPOSE : Reads command line. Loads arguments into structure. 
 * 1. Allocates memory for structure.
 * 2. Parses and rearranges arguments. i.e: "ls -la" will be a single arg.
 * 3. Counts number of total commands. i.e: "ls -la" "wc -l" = 2 total args.
 * 4. Creates linked list to manage any number of commands. */
t_arguments	*shell_reader(char *envp[], char **builtin_str)
{
	char		*line;
	char		**table;
	t_arguments	*args;

//----------------------------------TO REMOVE
	//to do: parser
	char **argv;
//----------------------------------
	argv = NULL;
	args = NULL;
	line = read_shell_line();
	if (!line)
		return (NULL);
	argv = ft_split(line, ' ');
	free(line);
	table = split_commands(argv);
	args = arg_reader(count_commands(table), table, envp);
	args->builtin_str = builtin_str; ///TODO: move to other place
	init_builtin_func_arr(args->builtin_func); //TODO: move to other place
	args->argv = argv; //to do: this will not be neccesary once structs are unified
	args->status = 0;
	return (args);
}