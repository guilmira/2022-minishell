/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:38:55 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/09 10:23:47 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Tokens in existance. */
static void	init_options(char **option, char **option_name)
{
	option[0] = "|";
	option_name[0] = "lex_PIPE";
	option[1] = "$";
	option_name[1] = "lex_DOLLAR";
	option[2] = "<";
	option_name[2] = "lex_INPUT";
	option[3] = ">";
	option_name[3] = "lex_OUTPUT";
	option[4] = ">>";
	option_name[4] = "lex_2INPUT";
	option[5] = ">>";
	option_name[5] = "lex_2OUTPUT";
	option[6] = NULL;
	option_name[6] = NULL;
}

/** PURPOSE : Filter tokens. */
static char	*obtain_syntax(char *token)
{
	int		i;
	char	*option[TOTAL_SYMBOLS + 1];
	char	*option_name[TOTAL_SYMBOLS + 1];

	init_options(option, option_name);
	i = -1;
	while (option[++i])
	{
		if (ft_strcmp(token, option[i]) == 0)
			return (option_name[i]);
	}
	return (0);
}

/** PURPOSE : Coonstruct lexer table. It will substitute
 * symbols like the pipe for its corresponding identfier (lex_PIPE) */
static char	**build_lexer_table(char **table)
{
	int		i;
	char	*syntax;

	if (!table)
		return (NULL);
	i = -1;
	while (table[++i])
	{
		syntax = obtain_syntax(table[i]);
		if (syntax)
		{
			free(table[i]);
			table[i] = ft_strdup(syntax);
			if (!table[i])
			{
				ft_free_split(table);
				return (NULL);
			}
		}
	}
	return (table);
}

/** PURPOSE : Lexical Analyzer. 
 * Corrects command line after reading it and interprets symbols. */
char	**main_lexer(char *line)
{
	char	**clean_line;
	char	**lexer_table;

	if (!line)
		return (NULL);
	lexer_table = NULL;
	if (!ft_strchr(line, '\"') && !ft_strchr(line, '\''))
		clean_line = ft_split(line, ' ');
	else
		clean_line = quote_split(line, ' ');
	lexer_table = build_lexer_table(clean_line);
	lexer_table = remove_quote(lexer_table);
	return (lexer_table);
}
