/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:38:55 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/06 15:25:16 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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

char	**build_lexer_table(char **table)
{
	int	i;
	char *syntax;

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
		//printf("%s\n", table[i]);
	}
	return (table);
}

/** PURPOSE : Lexical Analyzer. */
char	**main_lexer(char *line)
{
	char	**split_line;
	char	**lexer_table;
	
	if (!line)
		return (NULL);
	split_line = NULL;
	lexer_table = NULL;
	split_line = ft_split(line, ' ');
	lexer_table = build_lexer_table(split_line);
	return (lexer_table);
}