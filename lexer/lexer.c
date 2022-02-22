/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:38:55 by guilmira          #+#    #+#             */
/*   Updated: 2022/02/22 11:38:38 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Tokens in existence. */
void	init_options(char **option, char **option_name)
{
	option[0] = "|";
	option_name[0] = "lex_PIPE";
	option[1] = "<";
	option_name[1] = "lex_INPUT";
	option[2] = ">";
	option_name[2] = "lex_OUTPUT";
	option[3] = ">>";
	option_name[3] = "lex_APPEND";
	option[4] = "<<";
	option_name[4] = "lex_HEREDOC";
	option[5] = NULL;
	option_name[5] = NULL;
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

/** PURPOSE : Check if there are two lexer units next to each other. */
int	check_lexer_errors(char **table)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (table[++i])
	{
		if (!ft_strncmp("lex_", table[i], 4))
			flag++;
		else
			flag = 0;
		if (flag == 2)
			return (1);
	}
	return (0);
}

/** PURPOSE : Lexical Analyzer. 
 * Corrects command line after reading it and interprets symbols. */
char	**main_lexer(char *line, t_arguments *args)
{
	char	**clean_line;
	char	**lexer_table;
	char	*list_line;
	t_list	*list;

	if (!line)
		return (NULL);
	lexer_table = NULL;
	list = build_lexer_list(line);
	list_line = build_new_line(list);
	//printf("RESULT: %s\n", list_line);
	args->argv = ft_split(list_line, ' ');
	if (!args->argv)
		ft_shutdown(MEM, errno, args);
	ft_fullclear(list);
	if (!ft_strchr(list_line, DOUBLE) && !ft_strchr(list_line, SINGLE))
		clean_line = ft_split(list_line, ' ');
	else
		clean_line = quote_split(list_line, ' ');
	free(list_line);
	lexer_table = build_lexer_table(clean_line);
	if (check_lexer_errors(lexer_table))
	{
		args->flag_execution = 1;
		printf("Lexer symbols cant be together\n");
		ft_free_split(lexer_table);
		return (NULL);
	}
	lexer_table = remove_quote(lexer_table);
	system("leaks minishell");
	return (lexer_table);
}
