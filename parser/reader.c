/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:35:59 by guilmira          #+#    #+#             */
/*   Updated: 2022/03/13 14:08:31 by guilmira         ###   ########.fr       */
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

/** PURPOSE : Obtain COMMAND line and apply an initial filter. */
char	*read_and_filter_line(t_arguments *args)
{
	char	*line;

	line = read_shell_line();
	if (!line)
		return (NULL);
	if (pre_filter(line))
	{
		free(line);
		return (EMPTY_LINE);
	}
	args->flag_execution = 1;
	return (line);
}

/** PURPOSE : Check if string only has spaces. */
static int	case_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isspaces(str[i]))
			return (0);
	return (1);
}

/** PURPOSE : Handles file creation (in case of multipe redirections). */
static int	file_redirections(char **lexer_table, int *lexer_type, \
t_arguments *args)
{
	//management_file(lexer_table, args);
	if (case_space(lexer_table[0]) || args->flag_file_in == -1 || args->flag_file_out == -1)
	{
		ft_free_split(lexer_table);
		free(lexer_type);
		if (args->flag_file_in)
			printf("%s: No such file or directory\n", args->file_input);
		if (args->flag_file_in == -1 || args->flag_file_out == -1)
			printf("File or directory not found\n");
		args->flag_execution = 1;
		return (0);
	}
	return (1);
}

/** PURPOSE : Reads command line. Loads arguments into structure. 
 * 1. Reads command line and applies a pre-filter.
 * 2. Parses and rearranges arguments. i.e: "ls -la" will be a single arg.
 * 3. Counts number of total commands. i.e: "ls -la" "wc -l" = 2 total args.
 * 4. Creates linked list to manage any number of commands. */
void
	shell_reader(t_arguments *args)
{
	char		*line;
	int			*lexer_type;
	char		**lexer_table;

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
	if (!file_redirections(lexer_table, lexer_type, args))
		return ;
	printer(lexer_table, lexer_type);
	arg_reader(lexer_table, lexer_type, args);
	ft_free_split(lexer_table);
	free(lexer_type);
}
