/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zobsoleto_backup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:43:37 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/06 15:04:40 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** PURPOSE : Evaluates whether char is a pipe. */
int	is_pipe(char z)
{
	return (z == '|');
}

/** PURPOSE : Evaluates whether char is a greater or lesser. */
int	is_file_symbol(char z)
{
	return (z == '<' || z == '>');
}

/** PURPOSE : Boolean that evaluates if text is part of a command.
 * Such is the case on <echo "text"> or <cat "text">. */
int	is_following_text(char *previous, char *text)
{
	if (is_file_symbol(text[0]))
		return (0);
	if (is_special(previous))
		return (1);
	return (0);
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

table = split_commands(lexer_table, args); //deberias proteger





//IS COMMAND

/** PURPOSE : Auxiliar function to evaluate if its command. */
static int	check_previous_place(char *previous)
{
	int	i;
	char	*option[TOTAL_SYMBOLS];
	char	*option_name[TOTAL_SYMBOLS];
	
	init_options(option, option_name);
	if (ft_strcmp(previous, option_name[0]) == 0) //el pipe
		return (1);
	i = 1;
	while (++i < 6)
		if (ft_strcmp(previous, option_name[i]) == 0) //los <<, <, >>, >
			return (0);
	if (is_sufix(previous[0])) //si es sufijo inmediatamente no es
		return (0);
	if (is_special(previous)) //si es especial inmeiatmaente no es
		return (0);
	return (1);
}

/** PURPOSE : Evaluate whether string input is command or not.
 * Assumption: the string table given has gone through lexical analyser. */
int	is_command(char **lexer_table, char *command, int position)
{
	if (!command)
		return (0);
	if (token_is_lexic(command))
		return (0);
	if (is_sufix(command[0]))
		return (0);
	if (position == 0)
		return (1); //estaria bien comprobar si abre fichero etc.
	if (!check_previous_place(lexer_table[position - 1]))
		return (0);
	return (1);
}
