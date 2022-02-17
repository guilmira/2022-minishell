/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:35:59 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/17 11:43:26 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ctrl + c complexity when several levels of ms. it has to close. it can work with PID

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

/** PURPOSE : Obtain COMMAND line and apply an initial filter. */
char	*read_and_filter_line(t_arguments *args)
{
	char	*line;

	line = read_shell_line();
	if (!line)
		ft_shutdown(LINE, errno, args);
	//args->status = 1;// I guess this line should be higher, so status is put before exit
	//NO NEED TO PUT STATUS HERE
	if (pre_filter(line))
	{
		free(line);
		return (EMPTY_LINE);
	}
	args->flag_execution = 1;
	return (line);
}

/** PURPOSE : Reads command line. Loads arguments into structure. 
 * 1. Reads command line and applies a pre-filter.
 * 2. Parses and rearranges arguments. i.e: "ls -la" will be a single arg.
 * 3. Counts number of total commands. i.e: "ls -la" "wc -l" = 2 total args.
 * 4. Creates linked list to manage any number of commands. */
void	shell_reader(char *envp[], t_arguments	*args)
{
	char		*line;
	char		**table;
	char		**lexer_table;
	int			*lexer_type;

	line = read_and_filter_line(args);
	if (!line)
		eof_exit(args);
	if (!line[0])
		return ;
	lexer_table = main_lexer(line, args);
	free(line);
	if (!lexer_table)
		return ;
	lexer_type = class_lex_table(lexer_table);
	if (!lexer_type)
		ft_shutdown(MEM, errno, args);
	table = NULL;
	printer(lexer_table, lexer_type);
	table = get_command_table(lexer_table, args, lexer_type);
	ft_free_split(lexer_table);
	free(lexer_type);
	arg_reader(count_table(args->argv), table, envp, args);
	ft_free_split(table);
}
