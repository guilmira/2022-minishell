/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:35:59 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/05 17:19:07 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Reads command line and allocates it into string.
 * If pointer line exists and is not empty, adds it to history. */
static char	*read_shell_line(void)
{
	char	*line;

	line = readline(MSHELL);
	if (!line)
		return (NULL);
	if (line[0])
		add_history(line);
	return (line);
}

/** PURPOSE : Count total number of tokens. */
static int	count_tokens(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (argv[++i])
		j++;
	return (j);
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
	char		**lexer_table;

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
	lexer_table = main_lexer(line);
	if (!lexer_table)
		return ;
	args->argv = ft_split(line, ' '); //deberias proteger
	free(line);
	table = split_commands(lexer_table, args); //deberias proteger
	ft_free_split(lexer_table);
	arg_reader(count_tokens(args->argv), table, envp, args);
	ft_free_split(table);
}
