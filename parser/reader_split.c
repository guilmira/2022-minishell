/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:53:32 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/05 18:12:29 by guilmira         ###   ########.fr       */
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
static int	find_first_command(char **lexer_table, char **table, t_arguments	*args)
{
	int	i;

	i = -1;
	while (lexer_table[++i])
	{
		if (is_command(lexer_table, lexer_table[i], i))
		{
			table[0] = ft_strdup(lexer_table[i]);
			if (!table [0])
				ft_shutdown(MEM, 0, args);
			break ;
		}
	}
	return (i - 1);
}


int is_lex_symbol(char *string) //temporal apra borrar
{
	if (!ft_strcmp(string, "lex_INPUT"))
		return (1);
	if (!ft_strcmp(string, "lex_OUTPUT"))
		return (1);
	return (0);
}

/** PURPOSE : Fills table with every command, including its command line options
 * 1. Detects first command and inserts it on position 0 of table.
 * 2. Checks if there is more content on argv, If there is, it will add it to the
 * command by using the following rules:
 * -> is it pipe? Do not add.
 * -> is it a sufix(command line option) or a text like echo "text". Then add
 * -> is it a command on its own? then it should go on next position. */
static void	build_table(char **lexer_table, char **table, t_arguments	*args)
{
	int	i;
	int	j;
	char *token;

	j = 0;
	i = find_first_command(lexer_table, table, args);
	/* while (lexer_table[++i])
	{
		if (!argv[i + 1])
			break ;
		if (is_pipe(argv[i + 1][0]))
			;
		else if (is_sufix(argv[i + 1][0]) \
		|| is_following_text(argv[i], argv[i + 1]))
			table[j] = build_new_string(table[j], argv[i + 1], args);
		else if (is_command(argv, argv[i + 1], i + 1))
			table[++j] = ft_strdup(argv[i + 1]);
	} */

	i = i + 1;
	token = NULL;
	while (lexer_table[++i])
	{
		token = lexer_table[i];
		if (!token)
			break ;
		if (token_is_lexic(token)) //o funcion de, si es pipe, then:
			;
		else if (is_lex_symbol(lexer_table[i - 1]))
			;
		else if (is_sufix(token[0]))
			table[j] = build_new_string(table[j], token, args);
		else if (is_command(lexer_table, lexer_table[i], i))
			table[++j] = ft_strdup(lexer_table[i]);
		else
			table[j] = build_new_string(table[j], token, args);
	}
	table[++j] = NULL;
}

/** PURPOSE : Count total number of commands. */
static int	count_commands(char **lexer_table)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (lexer_table[++i])
		if (is_command(lexer_table, lexer_table[i], i))
			j++;
	return (j);
}

/** PURPOSE : Creates a table with a FULL COMMAND in each position. 
 * i.e.:
 * table[0] = "ls -la"
 * table[1] = "wc -l"
 * table[2] = "grep this is an example" */
char	**split_commands(char **lexer_table, t_arguments *args)
{
	char	**table;

	table = NULL;
	args->total_commands = count_commands(lexer_table);
	table = ft_calloc(args->total_commands + 1, sizeof(char *));
	if (!table)
		ft_shut(MEM, 0);
	build_table(lexer_table, table, args);
	return (table);
}
